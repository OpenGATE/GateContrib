## Brachytherapy

This example illustrates the simulation of a brachytherapy treatment using a titanium capsule and a source of Iodine 125.

## Electron radiotherapy

This example describes the simulation of a Clinac 2100C linear accelerator operating in 6 MeV electron mode for a thoracic 
irradiation of a RANDO phantom.

!!Warning!! This example should only be used for illustration purpose. Due to NDA with manufacturer, the geometry of the 
devices provided in the macros have been modified and are not the real ones.

The linac head consists in :

`+ a vacuum window : exit window in beryllium`<br>
`+ a 6 MeV scattering foil : in tantalum`<br>
`+ an ionization chamber : kapton-air-copper slabs`<br>
`+ X and Y Jaws : defining a 20x20cm2 aperture adapted to the 10x10cm2 applicator`<br>
`+ a 10x10cm2 applicator`<br>
`+ a 10x10cm2 cerrobend cut-out`<br>
  

The source is described as a circular surface source. The electron spectrum is assumed to be Gaussian with a mean energy of 7.2 MeV and a standard deviation of 3%.
external beam therapy photon

This example illustrates a photon beam therapy in a patient CT image. The output is a 3D dose distribution map (with associated uncertainty). The phantom being a patient CT image, one needs to generate materials from the image Hounsfield units :

`/gate/HounsfieldMaterialGenerator/SetMaterialTable                      data/Schneider2000MaterialsTable.txt`<br>
`/gate/HounsfieldMaterialGenerator/SetDensityTable                       data/Schneider2000DensitiesTable.txt`<br>
`/gate/HounsfieldMaterialGenerator/SetDensityTolerance                   0.1 g/cm3`<br>
`/gate/HounsfieldMaterialGenerator/SetOutputMaterialDatabaseFilename     data/patient-HUmaterials.db`<br>
`/gate/HounsfieldMaterialGenerator/SetOutputHUMaterialFilename           data/patient-HU2mat.txt`<br>
`/gate/HounsfieldMaterialGenerator/Generate`<br>

After the conversion from HU to materilas, the patient CT is inserted as the simulation phantom :

`/gate/world/daughters/name                                   patient`<br>
`/gate/world/daughters/insert                                 ImageRegionalizedVolume`<br>
`/gate/geometry/setMaterialDatabase                           data/patient-HUmaterials.db`<br>
`/gate/patient/geometry/setHUToMaterialFile                   data/patient-HU2mat.txt`<br>
`/gate/patient/geometry/setImage                              data/patient-2mm.mhd     <==== real patient CT scan `<br>
`/gate/patient/placement/setTranslation                       0 0 0 mm`<br>
`/gate/patient/geometry/TranslateTheImageAtThisIsoCenter      109.7 99.3 146.2 mm`<br>

A DoseActor is used to store 3D distributions of dose/edep/uncertainty/nbHit into files (mhd image file format) :

`/gate/actor/addActor                                   DoseActor  doseDistribution`<br>
`/gate/actor/doseDistribution/attachTo    	            patient`<br>
`/gate/actor/doseDistribution/stepHitType               random`<br>
`/gate/actor/doseDistribution/setPosition               0 0 0 mm`<br>
`/gate/actor/doseDistribution/setVoxelSize              2 2 2 mm`<br>
`/gate/actor/doseDistribution/enableEdep                true`<br>
`/gate/actor/doseDistribution/enableUncertaintyEdep     true`<br>
`/gate/actor/doseDistribution/enableDose                true`<br>
`/gate/actor/doseDistribution/enableNumberOfHits        false`<br>
`/gate/actor/doseDistribution/save                      output/photon.mhd`<br>

## Molecular therapy I131

## Protontherapy

This example simulates a proton beam in a water box with a Pencil Beam Scanning source with a treatment plan obtained from a Treatment Planning System (TPS).

`/gate/source/addSource                      PBS TPSPencilBeam`<br>
`/gate/source/PBS/setTestFlag                false`<br>
`/gate/source/PBS/setPlan                    data/RTIPLAN.0912590.16.txt`<br>
`/gate/source/PBS/setFlatGenerationFlag      false`<br>
`/gate/source/PBS/setSourceDescriptionFile   data/Source-Properties.txt`<br>
