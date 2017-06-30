/***********************************
 *
 *
 *
 *
 *
************************************/


#include "WaveUtils.h"

#include <TFile.h>
#include <TNtuple.h>
#include <TTree.h>
#include <TH1F.h>
#include <TString.h>

TFile fout("pks.root","recreate");

TNtuple *nt = new TNtuple("nt","","ev:t:q:w:a:qsum");

TNtuple *nti = new TNtuple("nti","","ev:qsum:qsum2");

TNtuple *nte = new TNtuple("nte","","ev:np:q");

void Peaks(int run_number = 722) {

  TFile *f = TFile::Open( TString::Format("$WLS_PATH/examples/output%08d.root", run_number) );

  TTree *t = (TTree*)( f->Get("midas_data") );

  const int NSAMPLES = 262144;
  
  int adc_value[4][NSAMPLES];
  
  WaveUtils wu;

  TH1F h("h",";time sample [ns]; amplitude [ADC counts]",NSAMPLES,-0.5,NSAMPLES*4-0.5);
  
  for(int ev=0; ev < t->GetEntries()-1 ; ++ev) {
	//for(int ev=0; ev < 10 ; ++ev) {

    //if(ev!=11) continue;

    cout<<" event "<<ev<<endl;

    t->Draw("nsamples","","goff",1,ev+1);
    int nsamples_next = t->GetV1()[0];
    
    t->Draw("nsamples","","goff",1,ev);
    int nsamples = t->GetV1()[0];

    if( nsamples_next != NSAMPLES || nsamples != NSAMPLES ) {
	ev += 2;
	continue;
    }
	
    if(nsamples != NSAMPLES) continue;
	
    t->Draw("adc_value_0:Iteration$*4","","goff",1,ev);

    int N = t->GetSelectedRows();

    //if(N!=1000) continue;
    
    double *adc    = t->GetV1();
    double *sample = t->GetV2();

    for(int i=0; i<nsamples; ++i)
      if( int(adc[i])==0 ) continue;
      
    h.Reset();

    for(int i=0; i<nsamples; ++i) {

      int amp = int(adc[i]);
      
      h.SetBinContent(i+1,amp);
    }

    wu.FindPeaks(h,-1,50,nsamples);

    /*
    for(int b=1; b<=wu.fHistWave.GetNbinsX(); ++b){
      //wu.fHistWave.SetBinContent(b, wu.fHistWave.GetBinContent(b)+wu.fPedestal);
      //wu.fHistWave.SetBinContent(b,wu.fPedestal+gRandom->Gaus(0,1));
      //wu.fHistWave.SetBinContent(b,4000+gRandom->Gaus(0,1));
    }
    

    if(gRandom->Uniform()<0.5)
      for(int b=wu.fHistWave.FindBin(3500.);b<=wu.fHistWave.FindBin(3540.);++b)
        wu.fHistWave.SetBinContent(b,4000+5);
    */


    if( wu.fPedestalOK )
      for(int b=1, w=10; b<=1000; b+=w) {
	nti->Fill(ev,wu.fHistWave.Integral(b,b+w-1),0);
      }

    
    int npeaks = wu.peak_list.size();
    

    int nsel = 0;
    float totq = 0;
    
    for(int i=0; i<npeaks; ++i) {

      if( !wu.peak_list[i].isolated ) continue;
      if( wu.peak_list[i].quality!=0 ) continue;

      
      nsel++;
      totq += wu.peak_list[i].integ*1.;
      
      nt->Fill(ev
	      ,wu.peak_list[i].imax*4.
	      ,wu.peak_list[i].integ*1.
	      ,(wu.peak_list[i].ilast-wu.peak_list[i].ifirst+1)*1.
	      ,wu.peak_list[i].amp*1.
	      ,0
	      );

    // if(wu.fHistWave.GetEntries()>0) {
	//	  fout.cd();
	//	wu.fHistWave.Write("hWave",TObject::kOverwrite);
    // }
      
    }//

    
  }//ev


  fout.cd();

  nt->Write();
  nti->Write();
  nte->Write();

  
}//Peaks

