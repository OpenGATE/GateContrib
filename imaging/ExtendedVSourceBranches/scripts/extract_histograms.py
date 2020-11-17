#Author: Mateusz Bała
#About: Simple example how with support of 3 new branches extract information about energy deposition for different scenarios

from ROOT import *
import argparse
import os.path

parser = argparse.ArgumentParser()
parser.add_argument("-i", "--input", required=True, type=str, help="Path to the .root file created by the GATE outpu.t")
parser.add_argument("-o", "--output", required=True, type=str, help="Output directory path for generated histograms images.")
parser.add_argument("-t", "--tree", required=True, type=str, help="Hits tree name.")
args = vars(parser.parse_args())

#Gamma type
_not_gamma = 0
_single_gamma = 1
_annhiliation_gamma = 2
_prompt_gamma = 3

#Decay type
_unknown_decay = 0
_standard_decay = 1
_deexcitation_decay = 2

#Source type
_unknown_source = 0
_single_gamma_emitter = 1
_pPs = 2
_oPs = 3

def getEdepHist(name,bins,xmin,xmax):
 h = TH1D(name,"",bins,xmin,xmax)
 h.GetXaxis().SetTitle("#Delta E [keV]")
 h.GetYaxis().SetTitle("Counts")
 return h
 
def drawHist(canvas,hist,output_directory_path):
 hist.Draw("hist")
 canvas.Print(output_directory_path + "/" + hist.GetName() + ".png" )
 
def main():
 #Load parameters
 input_file_path = args["input"]
 output_directory_path =args["output"]
 tree_name = args["tree"]
 
 #Check if file exist
 if not os.path.isfile(input_file_path):
  print("Input file does not exist")
  return
 if not os.path.isdir(output_directory_path):
  print("Output directory does not exist")
 
 #Open file and get tree
 input_file = TFile(input_file_path,"READ")
 tree = input_file.Get(tree_name)
 
 bins = 605
 xmin = -10.5
 xmax = 1200.5
 
 h_tot_edep = getEdepHist("total_edep",bins,xmin,xmax)
 h_ann_pPs_edep = getEdepHist("pPs_annihilation_edep",bins,xmin,xmax) 
 h_ann_oPs_edep = getEdepHist("oPs_annihilation_edep",bins,xmin,xmax)
 h_sg_edep = getEdepHist("sg_edep",bins,xmin,xmax)
 h_prompt_edep = getEdepHist("prompt_edep",bins,xmin,xmax)
 h_std_edep = getEdepHist("standard_decay_edep",bins,xmin,xmax)
 h_deexc_edep = getEdepHist("deexcitation_decay_edep",bins,xmin,xmax)
 
 for entry in tree:
  process_name = entry.processName
  if not (process_name == "compt" or process_name == "Compton"):
   continue
   
  gamma_type = entry.gammaType
  decay_type = entry.decayType
  source_type = entry.sourceType
  dE = 1000.0*tree.edep 
  
  if gamma_type == _not_gamma:
   continue

  h_tot_edep.Fill(dE)

  if gamma_type == _annhiliation_gamma and source_type == _pPs:
   h_ann_pPs_edep.Fill(dE)
  if gamma_type == _annhiliation_gamma and source_type == _oPs:
   h_ann_oPs_edep.Fill(dE)
  if gamma_type == _single_gamma_emitter and source_type == _single_gamma_emitter:
   h_sg_edep.Fill(dE)
  if decay_type == _standard_decay:
   h_std_edep.Fill(dE)
  if decay_type == _deexcitation_decay:
   h_deexc_edep.Fill(dE)
  if gamma_type == _prompt_gamma:
   h_prompt_edep.Fill(dE)
      
 canvas = TCanvas("c")
 drawHist(canvas,h_tot_edep,output_directory_path)
 drawHist(canvas,h_ann_pPs_edep,output_directory_path)
 drawHist(canvas,h_ann_oPs_edep,output_directory_path)
 drawHist(canvas,h_sg_edep,output_directory_path)
 drawHist(canvas,h_prompt_edep,output_directory_path)
 drawHist(canvas,h_std_edep,output_directory_path)
 drawHist(canvas,h_deexc_edep,output_directory_path)
 
 input_file.Close()
 
if __name__ == "__main__":
 main()
