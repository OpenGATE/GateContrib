This example mimics a bioluminescence/fluorescence experiment. 
All macros are located in *macro* subfolder. 
In addition, a ROOT macro [*DrawBranches.C*] is available and draws all branches of the OpticalData tree into a postscript file.

![](http://wiki.opengatecollaboration.org/images/8/8c/OpticalImaging-experiments.png)

The optical imaging system is composed of an array of pixels, an electronic board and an angular aperture that limits the range of angles over which the optical system can accept light. The phantom is composed of a box of water and two layers made of either water, hypodermis or epidermis. In case of a bioluminescence experiment, the tumor is described as a voxelized source of optical photons and is positioned under the inner layer of the phantom. In case of a fluorescence experiment, we assigned the Rhodamine B fluorophore to each voxel of a voxelized tumor and positioned it under the inner layer of the phantom. The fluorophore is excited by two external beam light sources emitting optical photons towards the tumor.

These two experiments are available in the main folder through the following macros: bioluminescence.mac and fluorescence.mac. 
The voxelized source or phantom is available in voxelized-source-phantom with an attenuation file and an optical-flux file. 
These macros will generate a root output file with the OpticalData tree enabled and a binary file which corresponds to the GATE ProjectionSet 
on the XY plane (i.e detection plane). Using the root macros MakeBioluminescencePlots.C and MakeFluorescencePlots.C, 
you can read the root output file and draw the bioluminescent/fluorescent light that is detected by the optical system. 
In case of the fluorescence experiment, two plots are drawn: all detected light (any wavelength) and the fluorescent light 
(wavelength cut). The projection binary file (.bin and .hdr) can be viewed directly using Anatomist or Imagej. 
In case of the fluorescence experiment, an Upholder (uphold cut) was applied through the digitizer so the binary image illustrates
the fluorescent light.

The Materials.xml file is updated with several tissues properties at specific wavelengths (from literature): brain, kidney, epidermis and hypodermis but also with the emission spectra of the Fluorescein and Rhodamine B. 
