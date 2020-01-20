/** ----------------------
  Copyright (C): OpenGATE Collaboration
  This software is distributed under the terms
  of the GNU Lesser General  Public Licence (LGPL)
  See LICENSE.md for further details
  ----------------------*/
#ifndef Track_h
#define Track_h

#include "Hit.h"
#include <vector>

/** Author: Mateusz Bała
 *  Email: bala.mateusz@gmail.com
 *  Organization: J-PET (http://koza.if.uj.edu.pl/pet/)
 *  About class: Simple representation of track
 **/
class Track
{
 public:
  Track( const int& trackID, const int& parentID, const TVector3& source_position );
  void addHit( const Hit& hit );
  std::vector<Hit> getHits() const;
  unsigned int getHitsNumber() const;
  int getID() const;
  bool isWithoutParent() const;
  Hit* getLastHit();
  int getParentID() const;
  TVector3 getSourcePosition() const { return fSourcePosition; }

 private:
  std::vector<Hit> fHits = {};
  int fID = -1;
  int fParentID = -1;
  TVector3 fSourcePosition = TVector3( 0.0, 0.0, 0.0 );
  
};

#endif
