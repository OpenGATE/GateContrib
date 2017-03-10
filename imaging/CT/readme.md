**CT simulation**

The CT example simulation is made of an X-Rays conical source, with 6.8° angle emission, a CT scanner with 100x100
Silicon (0.5x0.5x1 mm3) pixels and a cylindrical phantom made of Water containing 4 balls (Aluminium, Glass, SpineBone, PVC). 
During the simulation 16,835,281 photons are detected.

![CT example simulation using GATE](http://wiki.opengatecollaboration.org/images/1/1c/CTsimulationScheme.png "CT example simulation using GATE")


There are 2 runs. Each run performs during 90 seconds. The phantom turns around its central axis at 1 deg per second.

**Building and Running AnalyzeCT.cpp**

Compile the C++ file (in the classic directory) with the following command:

`g++ -O3 `root-config -cflags -glibs` AnalyzeCT.cpp -o AnalyzeCT`

**Results**

![CT example simulation : Projections during the First (left) and second (right) run.](http://wiki.opengatecollaboration.org/images/7/79/CTexampleResults.png "CT example simulation : Projections during the First (left) and second (right) run.")

The above figure shows the Energy spectrum for the first and second projection (first and second run). For the first Run, from top-left to bottom-right, the plot shows the energy spectrum outside the phantom, in the phantom, behind the 2 Top balls and behind the 2 bottom balls. For the second Run, from top-left to bottom-right, the plot shows the energy spectrum behind the PVC ball, behind the Aluminium ball, behind the Glass ball and behind the Spine Bone ball. 
