## Description

This example shows how to use the different modes of UserSpectrum source (**Discrete Spectrum** (mode 1), **Histogram** (mode 2) 
and **Linear interpolation spectrum** (mode 3)).

## Set-up

The geometry consists in a world volume made of liquid water including one box (MainBox) made of liquid water.
Three isotropic point sources centered in the MainBox are created:
* one gamma source emitting particles from a discrete spectrum (mode 1),<br>
* one electron source emitting particles from a histogram (mode 2)<br>
* one electron source emitting particles from a linear interpolation spectrum (mode 3).<br>

Source descriptions are defined with txt file format:
The first line describe the mode value and the minimum energy.<br>
Following lines described energy(MeV) and probability values.

Text files are located in the data repository.

## Physics

The Geant4 Standard option 3 physics list is assigned to the world volume and the MainBox volume with a cut of 10 kilometers to 
avoid secondary particles. A KillActor (allocated to the MainBox) is used to kill primary particles when they are created (before all interactions).


## Output

All spectrum sources are saved with an EnergySpectrumActor.<br>
To analyse the spectrum with ROOT, use the plot.C macro file.
