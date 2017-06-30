#include<TVector3.h>
#include<TH2Poly.h>
#include<TH2F.h>
#include<TGraph.h>
#include<TFile.h>

struct crtdet_t {

  // panel 1 is stairs side
  // panel 2 is wall side
  
  crtdet_t() {

    float strip_w = 112.;
    
    for(int is=0; is<NSTR; ++is) {

      float y = (7302.+100*2+20.*2)/2.;

      //float x1 = 1565 + (is*strip_w+strip_w/2);
      // centered to 0
      float x1 = -886.6 + (is*strip_w+strip_w/2);
      
      float z1 = 1930 + strip_w*NSTR - (is*strip_w+strip_w/2);

      //float x2 = 1545 + (is*strip_w+strip_w/2);
      // centered to 0
      float x2 = -906.6 + (is*strip_w+strip_w/2);
      
      float z2 = 1910 + strip_w*NSTR - (is*strip_w+strip_w/2);
      
      strip_pos1[is].SetXYZ(x1,-y,z1);
      strip_pos2[is].SetXYZ(x2,y,z2);

      strip_pos[0][is].SetXYZ(x1,-y,0);
      strip_pos[1][is].SetXYZ(0,-y,z1);
      strip_pos[2][is].SetXYZ(0,y,z2);
      strip_pos[3][is].SetXYZ(x2,y,0);
      
    }

    hStrip1.SetNameTitle("hStrip1","plane V1/H2; strip id; strip id");
    hStrip1.SetBins(NSTR,-0.5,NSTR-0.5,NSTR,-0.5,NSTR-0.5);
    hStrip2.SetNameTitle("hStrip2","plane V2/H2; strip id; strip id");
    hStrip2.SetBins(NSTR,-0.5,NSTR-0.5,NSTR,-0.5,NSTR-0.5);

    hStrip1.SetStats(0);
    hStrip2.SetStats(0);
    
    for(int i=1;i<=NSTR;++i) {
      hStrip1.GetXaxis()->SetBinLabel(i,Form("%i",NSTR-i));
      hStrip1.GetYaxis()->SetBinLabel(i,Form("%i",NSTR-i));

      hStrip2.GetXaxis()->SetBinLabel(i,Form("%i",NSTR-i));
      hStrip2.GetYaxis()->SetBinLabel(i,Form("%i",NSTR-i));
    }
    
    

  }//ctor

  static const int NSTR = 16;
  TVector3 strip_pos1[NSTR];
  TVector3 strip_pos2[NSTR];
  TVector3 strip_pos[4][NSTR];
  

  TH2F hStrip1;
  TH2F hStrip2;
  
  
};//crtdet_t




TGraph* GetSquare(float xdl, float ydl, float xur, float yur) {

  TGraph *g = new TGraph();

  g->SetPoint(0,xdl,ydl);
  g->SetPoint(1,xdl,yur);
  g->SetPoint(2,xur,yur);
  g->SetPoint(3,xur,ydl);
  g->SetPoint(4,xdl,ydl);
 
  return g;

}//GetSquare








void THDet_RackView() {
  
  
  crtdet_t crt_t;

  TCanvas * cc1 = new TCanvas();
  TH2F * hh1 = new TH2F(crt_t.hStrip1);
  hh1->Draw();
  cc1->Update();		       
  TCanvas * cc2 = new TCanvas();
  TH2F * hh2 = new TH2F(crt_t.hStrip2);
  hh2->Draw();
  cc2->Update();


  TFile fout("fdet.root","recreate");

  
  TH2Poly *TH2Poly_YZ = new TH2Poly("hDet_YZ","",-5000.,+5000,0,6000);

  TH2Poly *TH2Poly_YX = new TH2Poly("hDet_YX","",-5000.,+5000,-5000,5000);
  

  TH2Poly_YZ->SetStats(0);

  TH2Poly_YX->SetStats(0);

  
  //
  //
  //
  float OuterHalfLen_Z  = 4900./2; //approx
  float OuterHalfLen_Y  = 7302./2;
  float OuterHalfLen_X  = 4903.2/2;

  //
  // Z
  //
  float Membr_HalfLen_Z   = 2000./2; //approx
  
  float FloorToMembr_Z    = 1511.32; 

  
  float MembrToFG_Z   = 618.08;
  float FloorToFG_Z   = 2129.4;
  float FG_HalfLen_Z  = 950./2;

  //
  // Y
  // 
  //Stairs or Door side
  float ExtToMembr_Stairs_Y = 1256.8;
  float ExtToMembr_Wall_Y   = 1253.;
  
  
  float MembrToFG_Stairs_Y  = 966.4;
  float MembrToFG_Wall_Y    = 660.5;

  float ExtToFG_Stairs_Y  = ExtToMembr_Stairs_Y + MembrToFG_Stairs_Y;
  float ExtToFG_Wall_Y    = ExtToMembr_Wall_Y   + MembrToFG_Wall_Y;


  // 
  // X 
  //
  float ExtToMembr_Rack_X = 1261;
  float ExtToMembr_CR_X   = 1261; //CR:clean room

  float MembrToFG_Rack_X = 613.27; 
  float MembrToFG_CR_X   = 612.43;

  float ExtToFG_Rack_X   = ExtToMembr_Rack_X +  MembrToFG_Rack_X;
  float ExtToFG_CR_X     = ExtToMembr_CR_X   +  MembrToFG_CR_X;
  
  float FG_HalfLen_X  = 1155.5/2;
  


  //
  // --------------  YZ -----------------
  //
  TGraph *outer_structure_YZ = GetSquare( -OuterHalfLen_Y
				       ,0
				       ,OuterHalfLen_Y
				       ,OuterHalfLen_Z*2
				      );

  TGraph *membrane_YZ = GetSquare( -OuterHalfLen_Y + ExtToMembr_Stairs_Y
				,FloorToMembr_Z
				,OuterHalfLen_Y - ExtToMembr_Wall_Y
				,FloorToMembr_Z + Membr_HalfLen_Z*2
				);

  TGraph *FG_YZ = GetSquare( -OuterHalfLen_Y + ExtToFG_Stairs_Y
			  ,FloorToFG_Z
			  ,OuterHalfLen_Y - ExtToFG_Wall_Y
			  ,FloorToFG_Z + FG_HalfLen_Z*2
			  );
  
  //Stairs Side
  TGraph *panel_1_YZ = GetSquare( -crt_t.strip_pos1[0].Y()-20, crt_t.strip_pos1[15].Z()
  				,-crt_t.strip_pos1[0].Y()+20, crt_t.strip_pos1[0].Z());

  //Wall Side
  TGraph *panel_2_YZ = GetSquare( -crt_t.strip_pos2[0].Y()-20, crt_t.strip_pos2[15].Z()
  				,-crt_t.strip_pos2[0].Y()+20, crt_t.strip_pos2[0].Z());


  //
  cout<<"panel_1: "<<-crt_t.strip_pos1[0].Y()-20
      <<", "<<-crt_t.strip_pos1[0].Y()+20
      <<", "<<crt_t.strip_pos1[15].Z()
      <<", "<<crt_t.strip_pos1[0].Z()<<endl;


  cout<<"panel_2: "<<-crt_t.strip_pos2[0].Y()-20
      <<", "<<-crt_t.strip_pos2[0].Y()+20
      <<", "<<crt_t.strip_pos2[15].Z()
      <<", "<<crt_t.strip_pos2[0].Z()<<endl;

  //
  // --------- YX -------------------
  //


  TGraph *outer_structure_YX = GetSquare( -OuterHalfLen_Y
				       ,-OuterHalfLen_X
				       ,OuterHalfLen_Y
				       ,OuterHalfLen_X
				      );

  TGraph *membrane_YX = GetSquare( -OuterHalfLen_Y + ExtToMembr_Stairs_Y
				,-OuterHalfLen_X + ExtToMembr_CR_X
				,OuterHalfLen_Y - ExtToMembr_Wall_Y  
				,OuterHalfLen_X - ExtToMembr_Rack_X
				   );
  
  TGraph *FG_YX = GetSquare( -OuterHalfLen_Y + ExtToFG_Stairs_Y
			  ,-OuterHalfLen_X + ExtToFG_CR_X
			  ,OuterHalfLen_Y - ExtToFG_Wall_Y
			  ,OuterHalfLen_X - ExtToFG_Rack_X
			  );

  // Stairs side
  /*
  TGraph *panel_1_YX = GetSquare( crt_t.strip_pos1[0].Y()-20
				  ,-OuterHalfLen_X+1565+112./2 
				  ,crt_t.strip_pos1[0].Y()+20
				  ,-OuterHalfLen_X+1565+112*16-112./2 
				  				  );
  */

  TGraph *panel_1_YX = GetSquare( crt_t.strip_pos1[0].Y()-20
				  ,crt_t.strip_pos1[0].X()
				  ,crt_t.strip_pos1[0].Y()+20
				  ,crt_t.strip_pos1[15].X()
				  );

  
  // Wall side
  /*
  TGraph *panel_2_YX = GetSquare( -crt_t.strip_pos1[0].Y()+20
				  ,-OuterHalfLen_X+1545+112./2 
				  ,-crt_t.strip_pos1[0].Y()-20
				  ,-OuterHalfLen_X+1545+112*16-112./2 
				  );
  */

  TGraph *panel_2_YX = GetSquare( -crt_t.strip_pos1[0].Y()+20
				  ,crt_t.strip_pos2[0].X()
				  ,-crt_t.strip_pos1[0].Y()-20
				  ,crt_t.strip_pos2[15].X()
				  );
  			      

  cout<<endl<<" Plane 1 "<<endl;
  for(int i=0; i<crtdet_t::NSTR; ++i) {
    crt_t.strip_pos1[i].Print();
  }//

  
  cout<<endl<<" Plane 2 "<<endl;
  for(int i=0; i<crtdet_t::NSTR; ++i) {
    crt_t.strip_pos2[i].Print();
  }//

  
  

  //
  //  YZ
  //
 outer_structure_YZ->SetLineWidth(2);

 membrane_YZ->SetLineWidth(2);
	      
 FG_YZ->SetLineWidth(2);
 FG_YZ->SetLineStyle(2);
 FG_YZ->SetLineColor(2);
	
 panel_1_YZ->SetLineColor(2);
 panel_2_YZ->SetLineColor(2);
 
	
 TH2Poly_YZ->AddBin(outer_structure_YZ);
 TH2Poly_YZ->AddBin(membrane_YZ);
 TH2Poly_YZ->AddBin(FG_YZ);


 TH2Poly_YZ->AddBin(panel_1_YZ);
 TH2Poly_YZ->AddBin(panel_2_YZ);

 
 TH2Poly_YZ->SetTitle("; Y [mm]; Z [mm]");
 TH2Poly_YZ->GetYaxis()->SetTitleOffset(1.5);
 TH2Poly_YZ->GetXaxis()->SetTitleOffset(1.5);


 TCanvas *cyz = new TCanvas("cyz","cyz");
 TH2Poly_YZ->Draw();


 //
 // YX
 //

 outer_structure_YX->SetLineWidth(2);

 membrane_YX->SetLineWidth(2);
	      
 FG_YX->SetLineWidth(2);
 FG_YX->SetLineStyle(2);
 FG_YX->SetLineColor(2);

 panel_1_YX->SetLineColor(2);
 panel_2_YX->SetLineColor(2);
 
 TH2Poly_YX->AddBin(outer_structure_YX);
 TH2Poly_YX->AddBin(membrane_YX);
 TH2Poly_YX->AddBin(FG_YX);

 TH2Poly_YX->AddBin(panel_1_YX);
 TH2Poly_YX->AddBin(panel_2_YX);
 
 TH2Poly_YX->SetTitle("; Y [mm]; X [mm]");
 TH2Poly_YX->GetYaxis()->SetTitleOffset(1.5);
 TH2Poly_YX->GetXaxis()->SetTitleOffset(1.5);


 TCanvas *cyx = new TCanvas("cyx","cyx");
 TH2Poly_YZ->Draw();
 TH2Poly_YX->Draw();



 //
 //  
 //

 TH2Poly_YZ->Write("",TObject::kOverwrite);
 TH2Poly_YX->Write("",TObject::kOverwrite);


 fout.Write();
 
  
}//THDet_RackView() 





void THDet() {


  THDet_RackView();

}//


