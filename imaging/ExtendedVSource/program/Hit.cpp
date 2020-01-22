/** ----------------------
  Copyright (C): OpenGATE Collaboration
  This software is distributed under the terms
  of the GNU Lesser General  Public Licence (LGPL)
  See LICENSE.md for further details
  ----------------------*/
#include "Hit.h"

Hit::Hit( const double& energy_deposition, const double& time, const int& n_compt_cristal, const TVector3& position, const TVector3& momentum )
{
 fEnergyDeposition = energy_deposition;
 fTime = time;
 fNComptonCristal = n_compt_cristal;
 fPosition = position;
 fMomentumDirection = momentum;
}

double Hit::getEnergyDeposition() const { return fEnergyDeposition; }

double Hit::getTime() const { return fTime; }

int Hit::getNComptonCristal() const { return fNComptonCristal; }
 
TVector3 Hit::getPosition() const { return fPosition; }
  
TVector3 Hit::getMomentumDirection() const { return fMomentumDirection; }

void Hit::addEnergyDeposition( const double& energy ) { fEnergyDeposition += energy; }
