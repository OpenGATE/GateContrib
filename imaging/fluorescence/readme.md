This example is dedicated to test the activation of the fluorescence process in function of the physicsList. 

The phantom is either geometric (box) or voxelized and its material is Iodine and Tungsten.

The source is an isotropic monoenergetic gamma emission. 

The EnergySpectrumActor with a gamma filter is used to obtain the histogram of the number of gamma detected in the volume as a 
function of the energy. If fluorescence is activated, the fluorescence x-ray lines as well as the incident energy peak are visible.

## In order to get the atom deexcitation processes :
* With the physicsList-builder : `/gate/physics/addPhysicsList emlivermore`
* With your own physicsList : `/gate/physics/addAtomDeexcitation`

In both case, all atom deexcitation processes are automatically activated (fluo, auger, PIXE) for all volume included in the 
simulation. You still have the possibility to disable those processes by using one of the following commands :  

`/process/em/fluo  false`              -> disable all deexcitation processes<br/>
`/process/em/auger false`              -> disable auger only<br/>
`/process/em/pixe  false`              -> disable PIXE only<br/>


## Interpretation of the results contained in .root :

Energy spectrum histogram : number of gamma detected in the volume in function of the energy
* if fluorescence is activated, the fluorescence x-ray lines as well as the incident energy pic are visible
* line energies can be used to confirm the result
* line intensities can be also take into account if the statistic is higher enough  
* bin number and energy range must be set according to the expected result
