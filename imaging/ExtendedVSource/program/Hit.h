/** ----------------------
  Copyright (C): OpenGATE Collaboration
  This software is distributed under the terms
  of the GNU Lesser General  Public Licence (LGPL)
  See LICENSE.md for further details
  ----------------------*/
#ifndef Hit_h
#define Hit_h

#include "TVector3.h"

/** Author: Mateusz Bała
 *  Email: bala.mateusz@gmail.com
 *  Organization: J-PET (http://koza.if.uj.edu.pl/pet/)
 *  About class: Simple representation of hit ( hit represents track steps )
 **/
class Hit
{
 public:
  Hit( const double& energy_deposition, const double& time, const int& n_compt_cristal, const TVector3& position, const TVector3& momentum );
 
  double getEnergyDeposition() const;
  double getTime() const;
  int getNComptonCristal() const;
  TVector3 getPosition() const;
  TVector3 getMomentumDirection() const;
  void addEnergyDeposition( const double& energy );

 private:
  double fEnergyDeposition = 0.0;
  double fTime = 0.0;
  int fNComptonCristal = 0;
  TVector3 fPosition = TVector3( 0.0, 0.0, 0.0 );
  TVector3 fMomentumDirection = TVector3( 0.0, 0.0, 0.0 );
};

#endif
