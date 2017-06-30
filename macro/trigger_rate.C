{

TFile *_file0 = TFile::Open("$WLS_DATA/output00000772.root");

double t_min = midas_data->GetMinimum("TimeStamp");
double t_max = midas_data->GetMaximum("TimeStamp");
double t_l = t_max-t_min;

TString s = Form("TimeStamp-%f>>h0(1000, 0, %f)", t_min, t_l);

midas_data->Draw(s,"", "goff");
h0->Scale(1000/t_l);

TString s1 = Form("TimeStamp-%f>>h1(1000, 0, %f)", t_min, t_l);
TString w1 = Form("crt_daq_match");
midas_data->Draw(s1,w1, "goff");
h1->Scale(1000/t_l);

TString s2 = Form("TimeStamp-%f>>h2(1000, 0, %f)", t_min, t_l);
TString w2 = Form("crt_daq_match&&crt_reco");
midas_data->Draw(s2,w2, "goff");
h2->Scale(1000/t_l);


TCanvas * c = new TCanvas();

gStyle->SetOptStat(0);

c->SetLogy(true);

h0->SetLineColor(kBlack);
h0->Draw();

h1->SetLineColor(kBlue);
h1->Draw("sames");

h2->SetLineColor(kRed);
h2->Draw("sames");

h0->SetTitle("External trigger rate");
h0->GetXaxis()->SetTitle("Run time [s]");
h0->GetYaxis()->SetTitle("Trigger rate [Hz]");
h0->GetYaxis()->SetRangeUser(1e-3,1);

c->Update();

std::cout<<"Noe: " << midas_data->GetEntries()   << " Rate: " << midas_data->GetEntries()/t_l   << " +/- " << sqrt(midas_data->GetEntries())/t_l   << std::endl;
std::cout<<"Noe: " << midas_data->GetEntries(w1) << " Rate: " << midas_data->GetEntries(w1)/t_l << " +/- " << sqrt(midas_data->GetEntries(w1))/t_l << std::endl;
std::cout<<"Noe: " << midas_data->GetEntries(w2) << " Rate: " << midas_data->GetEntries(w2)/t_l << " +/- " << sqrt(midas_data->GetEntries(w2))/t_l << std::endl;


//TTree *_tree = (TTree*)_file0->Get("midas_data");
//_tree->SetBranchStatus("*",0);
//
//Int_t TimeStamp;
//Int_t PrevTimeStamp;
//_tree->SetBranchStatus("TimeStamp",1);
//_tree->SetBranchAddress("TimeStamp",&TimeStamp);
//
//TH1F *hdt = new TH1F("hdt","Event #Delta t ; Time (ns); Counts",100,0,100);
//
//_tree->GetEntry(0);
//PrevTimeStamp=TimeStamp;
//
//UInt_t noe = _tree->GetEntries();
//
//for (UInt_t i = 1; i < noe; ++i) {
//
//	_tree->GetEntry(i);
//
//	Double_t Delta = PrevTimeStamp - TimeStamp;
//	hdt->Fill(Delta);
//	PrevTimeStamp = TimeStamp;
//	}
//
//TCanvas * cc = new TCanvas();
//hdt->Draw();
//cc->Update();

}