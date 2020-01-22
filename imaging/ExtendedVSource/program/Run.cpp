/** ----------------------
  Copyright (C): OpenGATE Collaboration
  This software is distributed under the terms
  of the GNU Lesser General  Public Licence (LGPL)
  See LICENSE.md for further details
  ----------------------*/
#include "Selector.h"
#include <cstdlib>
#include <exception>
/** Program: Positronium data plotter ( pdp )
 *  Author: Mateusz Bała
 *  Email: bala.mateusz@gmail.com
 *  Organization: J-PET (http://koza.if.uj.edu.pl/pet/)
 *  About program: This program analyses data from standarad GATE output ( for ROOT file ) for positronium decay models.
 *  Commands:
 *  @param: FILE_NAME - *.root file name ( from GATE output )
 *  @param: MODEL - for which positronium decay model user wants to present data ( pPs - parapositroniu, oPs - orthopositronium, Ps - mixed decay )
 *  @param: PROMPT_ENABLE - data contains signal from prompt gamma ( source was emitting prompt gammas )
 *  @param: PROMPT_DISABLE - data doesn't contain signal from prompt gamma ( source wasn't emitting prompt gammas )
 *  @param: BINS_TIME - bins number ( lifetime histogram )
 *  @param: MIN_TIME - minimal value on x-axis ( lifetime histogram )
 *  @param: MAX_TIME - maximal value on x-axis ( lifetime histogram )
 *  @param: BINS_POS - bins number ( source position histogram ) 
 *  @param: MIN_POS - minimal value on x-axis and y-axis
 *  @param: MAX_POS - maximal value on x-axis and y-axis
 *  @param: LIFETIME - theoretical positronium lifetime value ( if this value is set, then lifetime plot will contain theoretical curve )
 *
 *  EXAMPLE OF USAGE:
 *  ./psd FILE_NAME data.root MODEL pPs PROMPT_ENABLE BINS_TIME 100 MIN_TIME 0.0 MAX_TIME 1.0 BINS_POS 20 MIN_POS -1.0 MAX_POS 1.0
 **/

void executeCmd( Selector& s, char* argv[], int& index )
{
 std::string cmd = argv[index];
 
 if ( cmd == "FILE_NAME" ) { s.setFileName( std::string( argv[++index] ) ); }
 else if ( cmd == "MODEL" ) { s.setModel( std::string( argv[++index] ) ); }
 else if ( cmd == "PROMPT_ENABLE" ) { s.setEnablePrompt( true ); }
 else if ( cmd == "PROMPT_DISABLE" ) { s.setEnablePrompt( false ); } 
 else if ( cmd == "BINS_TIME" ) { s.setBinsTime( std::atoi( argv[++index] ) ); }
 else if ( cmd == "MIN_TIME" ) { s.setMinTime( std::atof( argv[++index] ) ); }
 else if ( cmd == "MAX_TIME" ) { s.setMaxTime( std::atof( argv[++index] ) ); }
 else if ( cmd == "BINS_POS" ) { s.setBinsPosition( std::atoi( argv[++index] ) ); }
 else if ( cmd == "MIN_POS" ) { s.setMinPosition( std::atof( argv[++index] ) ); }
 else if ( cmd == "MAX_POS" ) { s.setMaxPosition( std::atof( argv[++index] ) ); }
 else if ( cmd == "LIFETIME" ) { s.setLifetime(  std::atof( argv[++index] ) ); }
 else { throw std::runtime_error("Unknown command."); }
}

int main( int argc, char* argv[] ) 
{
 const int arg_required_number = 10 * 2 - 2;//minimal number of arguments
 if ( argc < arg_required_number )
 {
  std::cerr << "[ERROR] Unproper arguments number. " << std::endl;
  return 2;
 }

 try 
 {
  Selector s;

  for ( int index = 1; index < argc; ++index ) { executeCmd( s, argv, index ); }

  s.doJob();
 }
 catch ( std::exception& e )
 {
  std::cerr << e.what() << std::endl;
  return 1;
 }
}
