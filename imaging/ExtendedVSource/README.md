# ExtendedVSource

## About

**ExtendedVSource** is an extension of VSource which supports emission of photons from positronium decay and gamma particles from deexcitation ( also know as prompt gamma ).

The main features of the source:

* photon emission from positronium decay ( para- and ortho-)

* photon polarization included

* positronium lifetime included

* emission of deexcitation gamma

* backward compatibile with the VSource class

### Compatibility with actors
Actors which use method BeginOfEventAction to extract information about primaries will return false information ( by calling for event `GetPrimaryVertex()->GetPrimary()->GetKineticEnergy()` ).

To received proper information, it is recommended to use `UserSteppingAction` method and call track methods ( G4Track class: GetVertexPosition, GetVertexKineticEnergy, etc. ).

## Models

### Enabled models
This source support four models:

* single gamma ( sg ) - single photon emission

* para-positronium ( pPs ) - two-photon emission from pPs decay

* ortho-positronium ( oPs ) - three-photon emission from oPs decay

* positronium ( Ps ) - mixed emission ( mixed photon emission from oPs and pPs decays )

Additionally for each positronium decay model ( pPs, oPs, Ps ) the prompt gamma can be emitted.

## Annihilation photons and prompt gamma

Annihilation photons are generated in different vertex than the prompt gamma. If the user asks for promt gamma generation, every event will contain two vertices: 

* first for prompt gamma - with position (x,y,z) and time T0

* second for annihilation gammas - with position (x,y,z) and time T0 + t, where t corresponds to the positronium lifetime generated from exponential distribution.

## Commands

* **GateVSource commands**
 > User can use major part of commands enable for GateVSource.

* **setType**

 > *Allowed values*: pPs, oPs, Ps, sg
 
 > *Example:* `/gate/source/SourceName/setType pPs`

 > *Description:* Choose from which positronium decay model emit gammas: pPs - para-positronium ( decay on 2 gammas ), oPs - ortho-positronium ( decay on 3 gammas ), Ps - mixed positronium ( it depends on pPs ( oPs ) emission probability  - by default p(pPs) = 1.0, p(oPs) = 0.0 ). Additionally you can emit single gamma (sg option).

* **setEnableDeexcitation**
 > *Allowed values*: true, false

 > *Example:* `/gate/source/SourceName/setEnableDeexcitation true`

 > *Description:* Generate prompt gamma from positron source which precedes positronium formation and decay. If this option is set *true* then it will create additional vertex with prompt gamma. Depends on model prompt gamma will have different energy.

* **setFixedEmissionDirection**

 > *Allowed values*: value value value
 
 > *Example:* `/gate/source/SourceName/setFixedEmissionDirection 1.0 0.0 0.0`

 > *Description:* Set fixed emission direction of single gamma (if: `setType sg`) or prompt gamma (if: `setEnableDeexcitation true`)

* **setEnableFixedEmissionDirection**

 > *Allowed values*: true, false
 
 > *Example:* `/gate/source/SourceName/setEnableFixedEmissionDirection true`

 > *Description:* Set enable/disable fixed emission direction of single gamma ( prompt gamma )

* **setEmissionEnergy**

 > *Allowed values*: value unit
 
 > *Example:* `/gate/source/SourceName/setEmissionEnergy 120 keV`

 > *Description:* Set emission energy of single gamma ( but not prompt gamma )

* **setSeed**

 > *Allowed values*: any unsigned integer
 
 > *Example:* `/gate/source/SourceName/setSeed 12345`

 > *Description:* Set seed for random generator used by models.

* **setPostroniumLifetime**

 > *Allowed values*: positronium value unit
 
 > *Example:* `/gate/source/SourceName/setPostroniumLifetime oPs 100.0 ns`

 > *Description:* Set positronium lifetime. By default are used values of lifetime in vacuum. Lifetime for simulated positronium decay is randomly chosen from exponential distribution. Each annihilation gamma has time increased by this value.

* **setPromptGammaEnergy**

 > *Allowed values*: positronium value unit
 
 > *Example:* `/gate/source/SourceName/setPromptGammaEnergy 2000 keV`

 > *Description:* Set energy of prompt gamma ( deexcitation gamma ). 

* **setPositroniumFraction**

 > *Allowed values*: positronium value
 
 > *Example:* `/gate/source/SourceName/setPositroniumFraction pPs 0.6`

 > *Description:* Set probability of emitting gammas from pPs and oPs decay with value from 0.0 to 1.0. It is required to set probability for one positronium kind - second will be calculated automatically. 

## Examples of usage

Before start use of examples please build dedicated for this examples [program](program/)

[**Example 1**](Example_1/README.md)

 > pPs decay with prompt gamma ( single source )

[**Example 2**](Example_2/README.md)

 > oPs decay with prompt gamma ( single source )

[**Example 3**](Example_3/README.md)

 > mixed decay with prompt gamma ( single source )

[**Example 4**](Example_4/README.md)

 > pPs decay with prompt gamma ( four sources with different activities and prompt gamma energies )


