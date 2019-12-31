/** ----------------------
  Copyright (C): OpenGATE Collaboration
  This software is distributed under the terms
  of the GNU Lesser General  Public Licence (LGPL)
  See LICENSE.md for further details
  ----------------------*/
#include <iostream>
#include "Reader.h"

void Reader::start( const std::string& file_name )
{
 assert( file_name.size() > 0 );
 std::cout << "[INFO] Request to open file: " << file_name << std::endl;

 std::string root_file_name = file_name;

 if ( file_name.rfind( ".root" ) == std::string::npos ) { root_file_name += ".root"; }

 pFile = new TFile(  root_file_name.c_str(), "READ" );
 
 assert( pFile->IsOpen() );
 std::cout << "[INFO] File \"" << root_file_name <<  "\" successfuly opened" << std::endl;

 pTree = dynamic_cast<TTree*>( pFile->Get( kTreeName.c_str() ) );
 
 assert( pTree != nullptr );
 std::cout << "[INFO] Found tree : " << kTreeName << std::endl;

 tryAttachVariablesToBranches();

 fEntriesNumber = pTree->GetEntries();
 std::cout << "[INFO] Tree contains " << fEntriesNumber << " entries. " << std::endl;
 std::cout << "[INFO] Everything OK - access to data established" << std::endl;
}

bool Reader::readNextEntry()
{
 if ( !( fCurrentEntryIndex < fEntriesNumber ) ) { return false; }
 
 pTree->GetEntry( fCurrentEntryIndex++ );
 
 return true;
}

void Reader::tryAttachVariablesToBranches()
{
 std::cout << "[INFO] Attaching to branches - start " << std::endl;
 fEventID.tryAttach( *pTree );
 fTrackID.tryAttach( *pTree );
 fParentID.tryAttach( *pTree );
 fPDGCode.tryAttach( *pTree );
 fProcessName.tryAttach( *pTree );
 fEnergyDeposition.tryAttach( *pTree );
 fTime.tryAttach( *pTree );   
 fPositionX.tryAttach( *pTree );
 fPositionY.tryAttach( *pTree );
 fPositionZ.tryAttach( *pTree );
 fSourcePositionX.tryAttach( *pTree );
 fSourcePositionY.tryAttach( *pTree );
 fSourcePositionZ.tryAttach( *pTree );
 fMomentumDirectionX.tryAttach( *pTree );
 fMomentumDirectionY.tryAttach( *pTree );
 fMomentumDirectionZ.tryAttach( *pTree );
 fNCristalCompton.tryAttach( *pTree );
 std::cout << "[INFO] Attaching to branches - finished " << std::endl;
}

int Reader::getEventID() const { return fEventID.getValue(); }

int Reader::getTrackID() const { return fTrackID.getValue(); }

int Reader::getParentID() const { return fParentID.getValue(); }

int Reader::getPDGCode() const { return fPDGCode.getValue(); }

std::string Reader::getProcessName() const { return std::string(fProcessName.getTableFirstPtr()); }

double Reader::getEnergyDeposition() const { return fEnergyDeposition.getValue() * kEnergyScale; }
 
double Reader::getTime() const 
{ 
 return fTime.getValue() * kTimeScale;
}

TVector3 Reader::getPosition() const { return TVector3( fPositionX.getValue(), fPositionY.getValue(), fPositionZ.getValue() ) * kPositionScale; }

TVector3 Reader::getSourcePosition() const { return TVector3( fSourcePositionX.getValue(), fSourcePositionY.getValue(), fSourcePositionZ.getValue() ) * kPositionScale; }

TVector3 Reader::getMomentumDirection() const { return TVector3( fMomentumDirectionX.getValue(), fMomentumDirectionY.getValue(), fMomentumDirectionZ.getValue() ); }

int Reader::getNCristalCompton() const { return fNCristalCompton.getValue(); }
