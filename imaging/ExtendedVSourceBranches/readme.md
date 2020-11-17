
# Ouput branches for ExtendedVSource
**Author**: Mateusz Bała (bala.mateusz@gmail.com)

## About
Three extra branches to the tree in the GATE output file:
* gammaType
* decayType
* sourceType

Above branches describe precisely properties of gammas emitted by ExtendedVSource and simplify analysis of data.

Branches are present in the follow output modules:
* GateToRoot - standard ROOT output (in the _Hits_ tree)
* GateToTree - new unified tree output (in the *.hits.root file tree)

### Branches description

**gammaType** informs about gamma type:

| Value | Description | Details |
| --- | ---| --- |
| 0 | not gamma | gamma not emitted by ExtendedVource or other particles|
| 1 | single gamma | single gamma with defined energy |
| 2 | annihilation gamma| gamma from positronium decay|
| 3 | prompt gamma| gamma emitted from the atom (source of positronium) deexcitation |

**decayType** informs from which model of positronium (Ps) decay gamma were emitted:

| Value | Description | Details |
| --- | ---| --- |
| 0 | unknown | by default|
| 1 | standard | Ps decay ( annihilation gammas emission)|
| 2 | de-excitation | atom deexcitation (prompt gamma exmitted) + Ps decay|

**sourceType** informs what is a source of gamma:

| Value | Description | Details |
| --- | ---| --- |
| 0 | unknown| not emitted by ExtendedVSource|
| 1 | single | single gamma emitter|
| 2 | pPs | parapositronium|
| 3 | oPs| orthopositronium|

> **Gamma emitted by a source different from ExtendedVSource and other particles will have all three variables equal zero.**

## Example

### How-to
To run simulation: `Gate mac/Main.mac`

To generate histograms from standard output:

`python3 scripts/extract_histograms.py -i output/output.root -o output -t Hits`

To generate histograms from new unified tree output:

`python3 scripts/extract_histograms.py -i output/output.hits.root -o output -t tree`

### Output

**Source:**

3 point sources (ExtendedVSource):

1. parapositronium (pPs) decay and prompt gamma (1157 keV) emission

2. orthopositronium (oPs) decay without prompt gamma emission

3. single gamma (900 keV)

**Histograms:**

Using the introduced branches, one can easily filter the spectrum of the deposited energy by gamma in Compton scattering.

For example, the total spectrum of energy deposited by gamma in the Compton process has the form:

`gammaType != 0`

![Total energy deposition](output/total_edep.png)

Histogram of deposited energy:

* by annihilation gammas from pPs decay:

`gammaType == 2 and sourceType == 2`

![Annihilation gammas from pPs](output/pPs_annihilation_edep.png)

* by annihilation gammas from oPs decay:

`gammaType == 2 and sourceType == 3`

![Annihilation gammas from oPs](output/oPs_annihilation_edep.png)

* by single gamma (with initial energy 900 keV):

`gammaType == 1 and sourceType == 1`

![Single gamma](output/sg_edep.png)

* by prompt gamma (with initial energy 1157 keV):

`gammaType == 3`

![Prompt gamma](output/prompt_edep.png)

* by gamma from Ps decay not preceded by de-excitation of the source atom:

`gammaType != 0 and decayType == 1`

![standard decay](output/standard_decay_edep.png)

* by gamma from Ps decay preceded by de-excitation of the source atom:

`gammaType != 0 and decayType == 2`

![deexcitation decay](output/deexcitation_decay_edep.png)
