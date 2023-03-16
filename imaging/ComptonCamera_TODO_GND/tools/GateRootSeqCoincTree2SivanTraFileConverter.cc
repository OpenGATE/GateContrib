#include <cstdlib>
#include "GateSequenceCoincidenceTreeReader.hh"
#include "GateCCRootDefs.hh"
#include "GateCCCoincidenceDigi.hh"




#include "GateMiscFunctions.hh"



using std::cout;
using std::endl;
void writeTraEvent(GateComptonCameraCones aCone, int counter, std::ofstream &oss){
    oss<<"SE" <<'\n';
    oss<<"ET CO"<<'\n';
    oss<<"ID"<<" "<<counter<<'\n';
    oss<<"TI "<<0.000859089<<'\n';
    oss<<"SQ "<<2<<'\n';
    oss<<"CT 0 0"<<'\n';
    oss<<"TL 1"<<'\n';
    oss<<"TE 0"<<'\n';
    oss<<"CE "<<aCone.GetEnergyR()/keV<<" "<<0<<"   "<<aCone.GetEnergy1()/keV<<" "<<0<<'\n';
    oss<<"CD "<<aCone.GetPosition1().getX()/cm<<" "<<aCone.GetPosition1().getY()/cm<<" "<<aCone.GetPosition1().getZ()/cm<<"   "<<0<<" "<<0<<" "<<0<<"   "<<aCone.GetPosition2().getX()/cm<<" "<<aCone.GetPosition2().getY()/cm<<" "<<aCone.GetPosition2().getZ()/cm<<"   "<<0<<" "<<0<<" "<<0<<"   "<<0<<" "<<0<<" "<<0<<"   "<<0<<" "<<0<<" "<<0<<"   "<<'\n';
    oss<<"LA 8.67643 "<<'\n';
}


int main(int argc, char *argv[])
{

    // Usage
    std::ostringstream usage;
    usage << std::endl
          << "Gate_CC_RootSeqCoinTree2SivanTra_Converter" << std::endl
          << "Read   the SequenceCoincidenceTree  and with the information of a cone generate a .tra  megalib file format " << std::endl
          << "Usage : " << argv[0] << " <SequenceCoincidenceInput.root>" << std::endl;


    // Get user parameters
    if (argc != 2) {
        std::cout << "Need 2 parameters" << std::endl
                  << usage.str() << std::endl;
        exit(0);
    }
    std::string input_filePathName=argv[1];
     //Prepare output file

    std::string outputFilename = removeExtension(input_filePathName);
    outputFilename = outputFilename+ "_sivan.tra";

    // Create output file
    std::ofstream ossCones;
    OpenFileOutput(outputFilename, ossCones);

   int coincCounter=0;
    GateSequenceCoincidenceTreeReader* m_coincFileReader= new GateSequenceCoincidenceTreeReader(input_filePathName);
         m_coincFileReader->PrepareAcquisition();
         //Saca un pulseList por cada eventID with the corresponfing number of pulses
         while( m_coincFileReader->hasNext()){
             //cout<<"prepareNext"<<endl;
              int isgood=m_coincFileReader->PrepareNextEventIdeal();
	     //if(isgood==1){
             if(isgood==1 && m_coincFileReader->PrepareEndOfEvent().GetTrueFlag()==true){
                 coincCounter++;
                writeTraEvent( m_coincFileReader->PrepareEndOfEvent(), coincCounter,ossCones);
             }
           }
    return 0;
}

