
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

This example perform simulation of a planar SPECT image from a voxelized source ... TODO !

## Visualisation

To visualise:

1. Comment `/vis/disable` (add # at the beginning of the line)
2. Uncomment `/control/execute mac/visualisation.mac` (remove the # at the beginning of the line)
3. Consider a very low number of particle (10-50 max)
4. Optional: the collimator make the visualisation very slow. You may disabled it by commenting the line `/control/execute mac/collimatorSPECT.mac`

