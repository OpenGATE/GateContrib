**Angular Response Function (ARF) Tables Data computation**

In this step, the data needed to generate the ARF tables are computed from a rectangular source located at the center of the field of view. The SPECT head is duplicated twice and located at roughly 30 cm from the axial axis. The command to tell GATE to compute the ARF data is:

`/gate/systems/SPECThead/arf/setARFStage generateData`

The ARF data are stored in the ROOT format from the GATE command output :

`/gate/output/arf/root/setARFDataFileName testARFdata`

By default the maximum size of a ROOT file is 1.8 Gb. Once the file has reached this size, ROOT automatically closes it and open a new file name testARFdata_1.root. when this file reaches 1.8 Gb, it is closed and a new file testARFdata_2.root if needed is created and so on ...

A template macro file is provided in gate_v4.0.0/examples/example_ARF/generateARFdata.mac which summarizes the commands listed before.
Computation of the ARF tables from ARF data (previous step)

Now that the data have been stored to ROOT files, we may compute the tables and store them to a binary file :

COMPUTE THE ARF TABLES FROM ARF DATA

`/gate/systems/SPECThead/arf/setARFStage computeTables`

DIGITIZER PART OF THE ARF SENSISTIVE DETECTOR

`/gate/systems/SPECThead/ARFTables/setEnergyDepositionThreshHold      328. keV

/gate/systems/SPECThead/ARFTables/setEnergyDepositionUpHold           400. keV

/gate/systems/SPECThead/ARFTables/setEnergyResolution                 0.10

/gate/systems/SPECThead/ARFTables/setEnergyOfReference                140. keV`

Here we shot 364.5 keV photons. We choose an energy resolution of 10% from which we obtain 328 keV and 400 keV as the energy window boundaries. The energy of reference is chosen to be 140 keV which allows to define the FWHM of the response of the detector as FWHM = 0.10 x sqrt(140. x Edep ), where Edep is the photon deposited energy.

If we do not want to consider photons which deposit less than 130 keV we may use:

`/gate/systems/SPECThead/setEnergyDepositionThreshHold 130. keV`

The ARF tables depend strongly on the distance from the detector to the source. We have to enter this parameter to get proper tables. The detector plane is set to be the half—middle plan of the detector part of the SPECT head. In the given example, we set the translation of the SPECT head to be 34.5 cm along the X direction (radial axis), the detector is 2 cm wide along X and its center is located at X = 1.5 cm with respect to the SPECThead frame. This is what we call the detector plane ( x = 1.5 cm ). So the distance from the source to the detector plane is 34.5 +1.5 = 36 cm :

`# DISTANCE FROM SOURCE TO DETECTOR PLANE TAKEN TO BE THE PLANE AT HALF DIMENSION OF THE CRYSTAL RESPECTIVELY TO THE SPECTHEAD FRAME
/gate/systems/SPECThead/ARFTables/setDistanceFromSourceToDetector 36 cm`

Now we compute the ARF tables from a text file which contains informations regarding the incident photons called ARFData.txt (provided in gate/examples/example_ARF).

`# NOW WE ARE READY TO COMPUTE THE ARF TABLES
/gate/systems/SPECThead/ARFTables/ComputeTablesFromEnergyWindows ARFData.txt`

The ARFData.txt file reads like this :

`# This file contains all the energy windows computed during first step with their associated root files
# It has to be formatted the following way : 
# [Emin,Emax] is the energy window of the incident photons
# The Base FileName is the the name of the root files name.root, name_1.root name_2.root ...
# The number of these files has to be given as the last parameter.
#
# Enter the datas for each energy window : 
# Inident Energy Window : Emin (keV) - Emax (keV) | Associated Root Base FileName | number of these files

0.    365.    test1head    20`

Here we have only one incident energy window for which we want to compute the corresponding ARF tables. The data for the first one are stored inside 20 files whose base file name is test1head which were generated in the previous stage. It means the ARF data are stored in test1head.root, test1head_1.root ... test1head_20.root.

Finally we store the computed tables to a binary file :

`/gate/systems/SPECThead/ARFTables/list
# SAVE ARF TABLES TO A BINARY FILE FOR PRODUCTION USE
/gate/systems/SPECThead/ARFTables/saveARFTablesToBinaryFile ARFSPECTBench.bin`

**Use of the ARF Tables**

The command to tell GATE to use the ARF tables is :

`/gate/systems/SPECThead/arf/setARFStage useTables`

The ARF sensitive detector is attached to the SPECThead :

`/gate/SPECThead/attachARFSD`

These tables are loaded from binary files with :

`/gate/systems/SPECThead/ARFTables/loadARFTablesFromBinaryFile ARFTables.bin`

