#if !defined(__CINT__) || defined(__MAKECINT__)
#include <TH1F.h>
#include <TH1D.h>
#include <TH2F.h>
#include <TAxis.h>
#include <TGraphErrors.h>	
#include <TMultiGraph.h>
#include <TMath.h>
#include <TF1.h>
#include <TLegend.h>
#include <TFile.h>
#include <TParticle.h>
#include <TString.h>
#include <TFile.h> 
#include <TTree.h> 
#include <Riostream.h> 
#endif


// generate ascii 2D output 


Bool_t ouput2DAscii() {

  Float_t zmin=1;
  Float_t zmax=401;
  Float_t ymin=-200;
  Float_t ymax=200;
  Int_t nbinsy = 401;
  Int_t nbinsz = 401;
  
  TH2F* hmap=new TH2F("hmap","",401,-200,200,401,-200,200); 
  TH2F* hmapnew=new TH2F("hmapnew","",nbinsz,zmin,zmax,nbinsy,ymin,ymax);

  TFile* dosemap=new TFile("output/dose-mapY-Edep.root");
  dosemap->GetObject("histo",hmap);

   string outputfileName="YZ-values-GATE-240MeV-1.5T-water.dat";
   //output file
   ofstream outputfile(outputfileName.c_str());
   if(!outputfile.good()) {
     std::cerr << "Could not open beam data output file "<<outputfileName<<"\n";
     return -1;
   }
   

    for(Int_t ibin=0;ibin<nbinsz;ibin++){
    for(Int_t jbin=0;jbin<nbinsz;jbin++){
    if((hmap->GetBinContent(ibin,jbin)>0)){
       Float_t value=hmap->GetBinContent(ibin,jbin);
       hmapnew->SetBinContent(ibin,jbin,value,value); 
       }
    }
    }
  
//  Rescale the 2d Histo Z
//  Int_t nbinsz = hmap.GetYaxis()->GetNbins();
 
Double_t ValuesArray[401][401];
     
for(Int_t ibin=0;ibin<nbinsz;ibin++){
	
	TH1D *hpyf = hmapnew->ProjectionY("hpyf",ibin,ibin,"");
	for(Int_t jbin=0;jbin<nbinsy;jbin++){
	ValuesArray[ibin][jbin] =  hpyf->GetBinContent(jbin);
	}
	
	delete hpyf;    
    }
        
// generate matrix ascii file
    Int_t row = 401;
    Int_t col = 401;
    
  for (int count=1; count < row; count ++)
        {
            for (int index=1; index < col; index++) 
                outputfile << ValuesArray[count][index] << " ";   //Space between each character
                outputfile << endl;  
                                            //New line for each row
        }
        
 //close beamDataOutput
 outputfile.flush();
 outputfile.close(); 

TCanvas *c1 = new TCanvas("c1","c1",1000,800);
c1->cd();
hmapnew->Draw();

return kTRUE;
     
      
}
