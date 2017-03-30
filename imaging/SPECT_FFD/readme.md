
# Fast SPECT simulation with Fixed Forced Detection

## Author: 
Thomas Cajgfinger, David Sarrut, Adrien Halty, Manon Jacquemin, Ludovic Ferrer

## Requirements: 
Gate *MUST* be compiled with RTK option enabled (set GATE_USE_RTK to ON in cmake).

## Usage:
- `Gate mac/monteCarloSPECT.mac`
- `Gate mac/angularResponseFunctionSPECT.mac`
- `Gate mac/fixedForcedDetectionSPECT.mac`

## Description

This is an example simulation of a planar SPECT image from a source (10cm cube) inside a voxelised water phantom (20cm cube).
The source emits 140.5 keV gammas (99mTC).
The image is a 100 by 100 4x4mm pixel projection in an energy window of 140.5 +/- 10%.

monteCarloSPECT.mac gives the analog MC simulation. 
angularResponseFunctionSPECT gives the simulation with the SPECT head replaced with ARF tables. 
mac/fixedForcedDetectionSPECT.mac gives the simulation with the FFD linked with ARF tables. 

The scatter window (120 +/- 5% keV) can be activated by commenting the primary window and uncommenting the scatter window. 
## Visualisation

To visualise:

1. Comment `/vis/disable` (add # at the beginning of the line)
2. Uncomment `/control/execute mac/visualisation.mac` (remove the # at the beginning of the line)
3. Consider a very low number of particle (10-50 max)
4. Optional: the collimator make the visualisation very slow. You may disabled it by commenting the line `/control/execute mac/collimatorSPECT.mac`

