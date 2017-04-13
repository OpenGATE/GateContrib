=======================================
        GATE - TEPC actor
=======================================

Authors:  F. Smekens, L. Maigne*
Laboratoire de Physique de Clermont, UMR6533 University Clermont Auvergne CNRS/IN2P3 - France
* Corresponding author: lydia.maigne@clermont.in2p3.fr


---> Description

This example shows how to use the TEPC actor in order to register the lineal energy transfer (LET) distribution using a TEPC detector geometry.
This detector has the specificity to mimic the shape and composition of structures (about 1 um of diameter) sensitive to radiation in a cell nucleus.
The final LET distribution is generally used to calculate the biological dose for high LET radiation or to characterize the beam quality for radioprotection issues.

---> Set-up

The geometry consists in a spherical TEPC detector positioned in a water tank. The TEPC is composed of a wall of A-150 plastic of 1.27 mm width and a low pressure tissue-equivalent gas cavity of 12.7 mm radius.
This geometry is irradiated with a circular (radius of 25 mm) monoenergetic 155 MeV proton beam.
The TEPC detector can be positioned at two different depths along the Bragg dose profile in order to measure the LET distribution: (1) the plateau region at 50 mm and (2) the peak region at 160 mm.

---> Physics and cuts

The QGSP_BIC_HP physicsList is set up following the recommendations concerning medical applications using protons. 
In order to optimize the computing time, the TEPC wall is subdivided into 5 regions where cuts and stepLimiters decrease from the outer to the inner region.

---> Output

The LET distribution is scored using a TEPC actor. Users have the possibility to set the energy range of the final distribution and to plot it using linear or logarithm scales. User can also tune the low pressure gas in the TEPC cavity. The final output is saved as a Root file. In order to observe the plots, the ROOT viewer will have to be set with the 'setLogX' and 'setLogY' options activated.

Note: a detailed description of the commands available for the TEPC actor can be found on the Gate/Geant4 wiki. The optimization of the cuts and stepLimiters for this TEPC geometry is also described.  

=======================================

