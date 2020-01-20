/** ----------------------
  Copyright (C): OpenGATE Collaboration
  This software is distributed under the terms
  of the GNU Lesser General  Public Licence (LGPL)
  See LICENSE.md for further details
  ----------------------*/
#include "Track.h"

Track::Track( const int& trackID, const int& parentID, const TVector3& source_position )
{
 fID = trackID;
 fParentID = parentID;
 fSourcePosition = source_position;
}

void Track::addHit( const Hit& hit ) { fHits.push_back( hit ); }
  
std::vector<Hit> Track::getHits() const { return fHits; }
  
unsigned int Track::getHitsNumber() const { return fHits.size(); }
  
int Track::getID() const { return fID; }
  
bool Track::isWithoutParent() const { return fParentID == 0; }

Hit* Track::getLastHit() { return &fHits[ fHits.size() - 1 ]; }

int Track::getParentID() const { return fParentID; }
