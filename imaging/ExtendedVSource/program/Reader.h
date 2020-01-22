/** ----------------------
  Copyright (C): OpenGATE Collaboration
  This software is distributed under the terms
  of the GNU Lesser General  Public Licence (LGPL)
  See LICENSE.md for further details
  ----------------------*/
#ifndef Reader_h
#define Reader_h

#include "TTree.h"
#include "TBranch.h"
#include "TMath.h"
#include "TFile.h"
#include "TVector3.h"
#include "TString.h"
#include "TObjString.h"
#include <string>
#include <cassert>
#include <memory>
#include <iostream>

/** Author: Mateusz Bała
 *  Email: bala.mateusz@gmail.com
 *  Organization: J-PET (http://koza.if.uj.edu.pl/pet/)
 *  About class: It facilitates access to branch data
 **/
template <class T, unsigned int table_size = 1>
class Variable
{
 public:
  Variable( const std::string& branch_name ) : fBranchName( branch_name ) { }

  void tryAttach( TTree& tree ) 
  { 
   std::cout << "[INFO] Attaching to branch: " << fBranchName << std::endl;
   assert( tree.FindBranch( fBranchName.c_str() ) != nullptr );
  
   tree.SetBranchAddress( fBranchName.c_str(), &fValue[0], &pBranch );
   assert( pBranch != nullptr );
  }
  const T getValue() const { return fValue[0]; }
  const T* getTableFirstPtr() const { return &fValue[0]; }

 private:
  std::string fBranchName = "";
  TBranch* pBranch = nullptr;
  T fValue[table_size];
  
};

/** Author: Mateusz Bała
 *  Email: bala.mateusz@gmail.com
 *  Organization: J-PET (http://koza.if.uj.edu.pl/pet/)
 *  About class: Reading standard GATE output file ( ROOT file )
 *  Each: 
 *  - time variable has unit in nanoseconds (ns)
 *  - space variable has unit in centimeters (cm)
 *  - energy variable has unit in kiloelectronovolts (keV)
 **/
class Reader
{
 public:
  Reader() {}
  ~Reader() { delete pFile; }

  void start( const std::string& file_name );
  bool readNextEntry();

  int getEventID() const;
  int getTrackID() const;
  int getParentID() const;
  int getPDGCode() const;
  std::string getProcessName() const;
  double getEnergyDeposition() const;
  double getTime() const;
  TVector3 getPosition() const;
  TVector3 getSourcePosition() const;
  TVector3 getMomentumDirection() const;
  int getNCristalCompton() const;

 private:
  void tryAttachVariablesToBranches();

 private:
  TFile* pFile = nullptr;
  TTree* pTree = nullptr;
  const std::string kTreeName = "Hits";

  int fEntriesNumber = 0;
  int fCurrentEntryIndex = 0;

  Variable<char,40> fProcessName = Variable<char,40>( "processName" );

  Variable<int> fEventID = Variable<int>( "eventID" );
  Variable<int> fTrackID = Variable<int>( "trackID" );
  Variable<int> fParentID = Variable<int>( "parentID" );
  Variable<int> fPDGCode = Variable<int>( "PDGEncoding" );
  Variable<float> fEnergyDeposition = Variable<float>( "edep" );
  Variable<double> fTime = Variable<double>( "time" );    
  Variable<float> fPositionX = Variable<float>( "posX" );
  Variable<float> fPositionY = Variable<float>( "posY" );
  Variable<float> fPositionZ = Variable<float>( "posZ" );   
  Variable<float> fSourcePositionX = Variable<float>( "sourcePosX" ); 
  Variable<float> fSourcePositionY = Variable<float>( "sourcePosY" ); 
  Variable<float> fSourcePositionZ = Variable<float>( "sourcePosZ" );
  Variable<float> fMomentumDirectionX = Variable<float>( "momDirX" );
  Variable<float> fMomentumDirectionY = Variable<float>( "momDirY" );
  Variable<float> fMomentumDirectionZ = Variable<float>( "momDirZ" );
  Variable<int> fNCristalCompton = Variable<int>( "nCrystalCompton" );

  const double kPositionScale =TMath::Power( 10.0, -1 ); // from mm to cm
  const double kEnergyScale = TMath::Power( 10.0, 3 ); // from MeV to keV
  const double kTimeScale = TMath::Power( 10.0, 9 ); //from s to ns
};

#endif
