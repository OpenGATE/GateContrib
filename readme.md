**GateContrib**

*(Warning: this is yet a tentative & experimental Gate sub-project. Contributions and suggestions welcome)*

[Gate](https://github.com/OpenGATE/Gate), based on [Geant4](https://geant4.web.cern.ch) library, allows to perform various Monte-Carlo simulations in the field of **medical physics**. [Gate](https://github.com/OpenGATE/Gate) can be used in numerous ways and for a lot of different applications. This repository contains [Gate](https://github.com/OpenGATE/Gate) simulation examples, mostly provided by users, in order to help sharing knowledge.

*Warning* - This repository contains data (binary files), stored with [git-lfs](https://git-lfs.github.com/) extension. EXPLAIN WHAT TO DO HERE

*Warning* - This is *user-oriented*, the provided examples are not tested and may not work. The [OpenGate collaboration](http://www.opengatecollaboration.org/) is not responsible of any contents.

----
**How to contribute ?**
* Prepare your example as a pull-request. Clone this repository in your github account, commit your example in your cloned repository, then ask us to integrate your proposal via the "New pull request" button. 
* Your simulation must be in a separate folder. You can put it in the folder `imaging` or `dosimetry` or `misc`. 
* Example **must** contains:
  * a `readme.md` file that describe the example, the authors, the date and Gate version
  * 3 folders `mac/` `data/` `output/`. The first will contains all macros (`.mac` files), the second all data files needed as input for the simulations. Results should be written in the `output/` folder. 
  * Simulation should be run by a command such as `Gate mac/main.mac` 
* It is also possible to contribute via **analysis tools**. If you developed a killer python script or C++ code useful for Gate simulation, feel free to share it here !



----
http://www.opengatecollaboration.org

References collaboration papers:
* 2004 http://www.ncbi.nlm.nih.gov/pubmed/15552416
* 2011 http://www.ncbi.nlm.nih.gov/pubmed/21248393
* 2014 http://www.ncbi.nlm.nih.gov/pubmed/24877844

