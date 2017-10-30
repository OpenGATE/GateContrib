/*
 * ------------------------------------
 * Author		Loic Grevillot
 * Version		0.1				First version
 * ------------------------------------
 * 
=======================================================================
LGPHSPROCESS MACRO PARAMETERS
=======================================================================
  myfile [input file path]
  out [output file path]
  part [particle under analysis] (usually primary beam)
  visu [display of histograms: true or false]
=======================================================================
*/ 
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;
//void LGPhSProcess(string myfile="./output/IsocenterPhS.root", string out="./results/Analyse_singlePhSFile4Spots.txt", string part="proton", bool visu=true){ 
//void LGPhSProcess(string myfile="./output/PhS-X50Y0.root", string out="./results/Analyse_singlePhSFile4Spots.txt", string part="proton", bool visu=true){ 
void LGPhSProcess(string myfile="./output/IsocenterPhS_GTRY90.root", string out="./results/Analyse_singlePhSFile4Spots.txt", string part="proton", bool visu=true){   
//----------------------------------------------------------------------------
// VARIABLES
 float EPHS;
 float xPHS, yPHS, zPHS;
 float dxPHS, dyPHS, dzPHS;
 float ThetaPHS, PhiPHS;
 float weightPHS;
 char volumeNamePHS[64];
 char particleNamePHS[64];
 char procNamePHS[64];

 float EIsocenter;
 float xIsocenter, yIsocenter, zIsocenter;
 float dxIsocenter, dyIsocenter, dzIsocenter;
 float weightIsocenter;
 char volumeNameIsocenter[64];
 char particleNameIsocenter[64];
 char procNameIsocenter[64];
 
//----------------------------------------------------------------------------
// PHS DECLARATION
 cout<<"Loading "<<myfile<<endl;
 TChain *  T_PHS = new TChain("PhaseSpace");
 T_PHS->Add(myfile.c_str());
 T_PHS->SetBranchAddress("ParticleName",&particleNamePHS);
//T_PHS->SetBranchAddress("ProductionVolume",&volumeNamePHS);
// T_PHS->SetBranchAddress("ProductionProcess",&procNamePHS);
 T_PHS->SetBranchAddress("Ekine",&EPHS);
 T_PHS->SetBranchAddress("X",&xPHS);
 T_PHS->SetBranchAddress("Y",&yPHS);
 T_PHS->SetBranchAddress("Z",&zPHS);
 T_PHS->SetBranchAddress("dX",&dxPHS);
 T_PHS->SetBranchAddress("dY",&dyPHS);
 T_PHS->SetBranchAddress("dZ",&dzPHS);
 T_PHS->SetBranchAddress("Weight",&weightPHS);
 //weightPHS=1;
cout<<" PhS loaded"<<endl;


//----------------------------------------------------------------------------
// HISTOGRAMS
// Defining the bin sizes
int nPHS = T_PHS->GetEntries(); 
cout<<" nPhS = "<<nPHS<<endl;
int jPHS = 0;
double Emoy=0.0;
double Xmoy=0.0;
double Ymoy=0.0;
double Wmoy=0.0;
//nPHS=1000000;
 for(int i = 0 ; i< nPHS; i++){
  T_PHS->GetEntry(i);
  TString pName = particleNamePHS;
  if (pName.Contains(part))
	{
	jPHS++;
	Emoy=Emoy+EPHS;
	Xmoy=Xmoy+xPHS;
	Ymoy=Ymoy+yPHS;
	Wmoy=Wmoy+weightPHS;
	}
	
 }
Emoy=Emoy/jPHS; 
Xmoy=Xmoy/jPHS;
Ymoy=Ymoy/jPHS;
Wmoy=Wmoy/jPHS;

//cout<<Emoy<<"   "<<Xmoy<<"   "<<Ymoy<<endl;

jPHS = 0;
double dE=0.0;
double dX=0.0;
double dY=0.0;
double dTheta=0.0;
double dPhi=0.0;
double dWeight=0.0;
 for(int i = 0 ; i< nPHS; i++){
  T_PHS->GetEntry(i);
  TString pName = particleNamePHS;
  if (pName.Contains(part))
	{
	jPHS++;
	dE=dE+(EPHS-Emoy)*(EPHS-Emoy);
	dX=dX+(xPHS-Xmoy)*(xPHS-Xmoy);
	dY=dY+(yPHS-Ymoy)*(yPHS-Ymoy);
  	dTheta=dTheta+(atan(dxPHS/dzPHS)*1000.-0.0)*(atan(dxPHS/dzPHS)*1000.-0.0);
	dPhi=dPhi+(atan(dyPHS/dzPHS)*1000.-0.0)*(atan(dyPHS/dzPHS)*1000.-0.0);
	dWeight=dWeight+(weightPHS-Wmoy)*(weightPHS-Wmoy);
	}
 }
dE=sqrt(dE/jPHS);
dX=sqrt(dX/jPHS);
dY=sqrt(dY/jPHS);
dTheta=sqrt(dTheta/jPHS);
dPhi=sqrt(dPhi/jPHS);
dWeight=sqrt(dWeight/jPHS);

 int nBins=200;
 int n=3;
 double eBin=n*dE;
 double xBin=n*dX;
 double yBin=n*dX;
 double thetaBin=n*dTheta;
 double phiBin=n*dPhi;
 double wBin=n*dWeight;

//----------------------------------------------------------------------------
// HISTOGRAMS
// Declaring the histograms 
 TH1D *histoDistriXPHS;
 TH1D *histoDistriYPHS;
 TH1D *histoDistriThetaPHS;
 TH1D *histoDistriPhiPHS;
 TH1D *histoEnergyPHS;
 TH1D *histoWeightPHS;
 TH2D *histoEmittanceXThetaPHS;
 TH2D *histoEmittanceYPhiPHS;
 histoDistriXPHS = new TH1D("histoDistriXPHS", "X", nBins, Xmoy-xBin, Xmoy+xBin);
 histoDistriYPHS = new TH1D("histoDistriYPHS", "Y", nBins, Ymoy-yBin, Ymoy+yBin);
 histoDistriThetaPHS = new TH1D("histoDistriThetaPHS", "#theta", nBins, -thetaBin, thetaBin);
 histoDistriPhiPHS = new TH1D("histoDistriPhiPHS", "#phi", nBins, -phiBin, phiBin);
 histoEnergyPHS = new TH1D("histoEnergyPHS", "E", nBins, Emoy-eBin, Emoy+eBin);
 histoWeightPHS = new TH1D("histoWeightPHS", "Weight", nBins, Wmoy-wBin, Wmoy+wBin);
 histoEmittanceXThetaPHS = new TH2D("histoEmittanceXThetaPHS", "Emittance X #theta",nBins, Xmoy-xBin, Xmoy+xBin, nBins, -thetaBin, thetaBin);
 histoEmittanceYPhiPHS = new TH2D("histoEmittanceYPhiPHS", "Emittance Y #phi",nBins, Ymoy-yBin, Ymoy+yBin, nBins, -phiBin, phiBin); 
 
//----------------------------------------------------------------------------
// PROCESSING 
  jPHS = 0;
//  Emoy=0.0;
  dE=0.0;
  double Emax=0.0, Emin=10000;
  double max=0.0, val=0.0;
 for(int i = 0 ; i< nPHS; i++){
   
  T_PHS->GetEntry(i);
  TString pName = particleNamePHS;
  if (pName.Contains(part))
	{
	jPHS++;
	histoDistriXPHS->Fill(xPHS,1);
  	histoDistriYPHS->Fill(yPHS,1);
	histoDistriThetaPHS->Fill(atan(dxPHS/dzPHS)*1000.,1);
	histoDistriPhiPHS->Fill(atan(dyPHS/dzPHS)*1000.,1);
	histoEnergyPHS->Fill(EPHS,1);  
	histoWeightPHS->Fill(weightPHS,1);
	histoEmittanceXThetaPHS->Fill(xPHS,atan(dxPHS/dzPHS)*1000.,1); // x-axis in mm and y-axis in mrad
	histoEmittanceYPhiPHS->Fill(yPHS,atan(dyPHS/dzPHS)*1000.,1);
//	Emoy=Emoy+EPHS;
// 	if (EPHS>Emax) {Emax=EPHS;}
// 	if (EPHS<Emin) {Emin=EPHS;}
	}
}
//	Emoy=Emoy/jPHS;
	
  for (int i=1; i<=nBins; i++){
    val=histoEnergyPHS->GetBinCenter(i);
    if (val>=Emoy) {
      max=histoEnergyPHS->GetBinContent(i);
      i=nBins+1;
    }
  }
//  cout<<"max  "<<max<<endl;
  for (int i=1; i<=nBins; i++){
    val=histoEnergyPHS->GetBinContent(i);
    if (val>max/2.) {
      Emin=histoEnergyPHS->GetBinCenter(i);
      i=nBins+1;
    }
  }
//  cout<<"Emin  "<<Emin<<endl;
  for (int i=nBins; i>0; i--){
    val=histoEnergyPHS->GetBinContent(i);
    if (val>max/2.) {
      Emax=histoEnergyPHS->GetBinCenter(i);
      i=0;
    }
  }
//  cout<<"Emax  "<<Emax<<endl;
//	dE=Emax-Emin;
	
	histoDistriXPHS->Fit("gaus");
	TF1 *fitX = histoDistriXPHS->GetFunction("gaus");
	histoDistriYPHS->Fit("gaus");
	TF1 *fitY = histoDistriYPHS->GetFunction("gaus");
histoEnergyPHS->Fit("gaus");
TF1 *fitE = histoEnergyPHS->GetFunction("gaus");
	histoDistriThetaPHS->Fit("gaus");
	TF1 *fitTheta = histoDistriThetaPHS->GetFunction("gaus");
	histoDistriPhiPHS->Fit("gaus");
	TF1 *fitPhi = histoDistriPhiPHS->GetFunction("gaus");
	xPHS=fitX->GetParameter(2);
	yPHS=fitY->GetParameter(2);
//	EPHS=fitE->GetParameter(1);
	dEPHS=fitE->GetParameter(2);
	ThetaPHS=fitTheta->GetParameter(2);
	PhiPHS=fitPhi->GetParameter(2);

cout<<"Nb Particles PHS= "<<nPHS<<endl;
cout<<"Nb primaries PHS= "<<jPHS<<endl;
cout<<"Energy avg: "<<Emoy<<" MeV\tEnergy-Spread (1-sigma): "<<dEPHS<<" MeV\tSpot X (1-sigma): "<<xPHS<<" mm\tY (1-sigma): "<<yPHS<<" mm\tDiv theta (1-sigma): "<<ThetaPHS<<" mrad\tphi (1-sigma): "<<PhiPHS<<" mrad\t Xavg: "<<Xmoy<<" mm\tYavg: "<<Ymoy<<" mm\tWeight avg: "<<Wmoy<<endl;

// WRITTING OUTPUTS  
  ifstream in;
  in.open(out.c_str());
  ofstream tmp;
  tmp.open("temp.txt");
  string temp="";
  while (getline(in,temp)){
    tmp<<temp<<endl;
    temp="";
  }
//  tmp<<myfile<<"\t"<<jPHS<<"\t"<<Emoy<<"\t"<<dE<<"\t"<<dE/Emoy*100.<<"\t"<<xPHS<<"\t"<<yPHS<<"\t"<<ThetaPHS<<"\t"<<PhiPHS<<"\t"<<Xmoy<<"\t"<<Ymoy<<endl;
tmp<<myfile<<"\t"<<jPHS<<"\t"<<Emoy<<"\t"<<dEPHS<<"\t"<<dEPHS/Emoy*100.<<"\t"<<xPHS<<"\t"<<yPHS<<"\t"<<ThetaPHS<<"\t"<<PhiPHS<<"\t"<<Xmoy<<"\t"<<Ymoy<<"\t"<<Wmoy<<endl;
  tmp.close();
  in.close();
  
  in.open("temp.txt");
  tmp.open(out.c_str());
  temp="";
  while (getline(in,temp)){
    tmp<<temp<<endl;
    temp="";
  }
  tmp.close();
  in.close();
  remove("temp.txt");

//----------------------------------------------------------------------------
// DISPLAY
if (visu){
gStyle->SetOptFit(1111);
gStyle->SetPalette(1);

histoDistriXPHS->SetTitle("X ");
histoDistriXPHS->SetYTitle("Nb particles");
histoDistriXPHS->SetXTitle("X (mm)");
histoDistriYPHS->SetTitle("Y ");
histoDistriYPHS->SetYTitle("Nb particles");
histoDistriYPHS->SetXTitle("Y (mm)");
histoDistriThetaPHS->SetTitle("#theta ");
histoDistriThetaPHS->SetYTitle("Nb particles");
histoDistriThetaPHS->SetXTitle("#theta (mm)");
histoDistriPhiPHS->SetTitle("#phi ");
histoDistriPhiPHS->SetYTitle("Nb particles");
histoDistriPhiPHS->SetXTitle("#phi (mm)");
histoEnergyPHS->SetTitle("Energy ");
histoEnergyPHS->SetYTitle("Nb particles");
histoEnergyPHS->SetXTitle("E (MeV)");
histoEmittanceXThetaPHS->SetTitle("Phase-space X-#theta ");
histoEmittanceXThetaPHS->SetYTitle("#theta (mrad)");
histoEmittanceXThetaPHS->SetXTitle("X (mm)");
histoEmittanceYPhiPHS->SetTitle("Phase-space Y-#phi ");
histoEmittanceYPhiPHS->SetYTitle("#phi (mrad)");
histoEmittanceYPhiPHS->SetXTitle("Y (mm)");

TCanvas * window = new TCanvas("window","Spot sizes and divergences",1);
TCanvas * fenetre2 = new TCanvas("fenetre2","Energy and Phase-spaces",1);

window->Divide(2,2);
window->cd(1);
histoDistriXPHS->Draw();
window->cd(2);
histoDistriYPHS->Draw();
window->cd(3);
histoDistriThetaPHS->Draw();
window->cd(4);
histoDistriPhiPHS->Draw();

fenetre2->Divide(2,2);
fenetre2->cd(1);
histoEnergyPHS->Draw();
fenetre2->cd(3);
histoEmittanceXThetaPHS->Draw("COLZ");
fenetre2->cd(4);
histoEmittanceYPhiPHS->Draw("COLZ");

}
}

