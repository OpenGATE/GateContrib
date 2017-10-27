/*
 * ------------------------------------
 * Author		Loic Grevillot
 * Version		0.1				First version
 * ------------------------------------
 * 
=======================================================================
LGPHSLISTPROCESS MACRO PARAMETERS
=======================================================================
  WorkDir [directory of list of files to be anaylsed]
  FileListName [input file containing the list of files to be processed]
  FileOut [output file path]
  part [particle under analysis] (usually primary beam)
=======================================================================
*/ 
#include <iostream>
#include <iomanip>
#include <fstream>
#include "LGPhSProcess.C"
using namespace std;
//void LGPhSListProcess(string WorkDir="./", string FileListName="./listPhS.txt", string FileOut="results/AnalysePhSs.txt", string part="proton"){
void LGPhSListProcess(string WorkDir="./", string FileListName="./listPhS.txt", string FileOut="results/AnalysePhSs.txt", string part=""){

// LOADING PREREQUISITE FUNCTIONS
//gROOT->ProcessLine(".L LGPhSProcess.C");
//gROOT->LoadMacro("LGPhSProcess.C");
    
// VARIABLES
 string temp="";
 string FileName="";
 string MyFile="";

// OPENING OUTPUT FILE
  temp.append(WorkDir);
  temp.append(FileOut);
  FileOut=temp;
  temp="";
  ofstream fileResults(FileOut.c_str());
  fileResults<<"File name\tNb particles\tE (MeV)\tdE(1-sigma) (MeV)\tdE(1-sigma) (%)\tX(1-sigma) (mm)\tY(1-sigma) (mm)\tTheta(1-sigma) (mrad)\tPhi(1-sigma) (mrad)\tXavg (mm)\t Yavg (mm)\t Weight avg"<<endl;
  fileResults.close();
  cout<<"\nOutput file: "<<FileOut<<endl;
  
// OPENING LIST FILE
  temp.append(WorkDir);
  temp.append(FileListName);
  FileListName=temp;
  temp="";
  ifstream Listfile(FileListName.c_str());
  if (Listfile.fail()){
    cout << "Opening file error "<<FileListName<<" - abort"<<endl; exit(0);
  }
  else {
    cout<<"List file: "<<FileListName<<" loaded."<<endl;
  }
  
// VERBOSE

  // DATA PROCESSING OF ALL LISTED FILES
  while (getline(Listfile,FileName)){
  MyFile.append(WorkDir);
  MyFile.append(FileName);
  LGPhSProcess(MyFile,FileOut,part,false);
//    LGPhSProcess(MyFile1,MyFile2,FileOut,"C12[0.0]",1400,false);
  MyFile="";
  }
}

