**GateContrib**

**Warning** - This is a *user-oriented*, collaborative repository of Gate examples. The [OpenGate collaboration](http://www.opengatecollaboration.org/) is not responsible of any contents.

**PLEASE INSTALL GIT-LFS FIRST: this is required !**  
This repository contains data (binary files), stored with [git-lfs](https://git-lfs.github.com/) extension. For most modern Linux distributions there is a standard package for this, e.g. for Ubuntu/Debian do: `apt install git-lfs`. (If your OS does not have a standard package for git-lfs, then follow the installation instructions on the [git-lfs GitHub page](https://git-lfs.github.com/).) With git-lfs successfully installed, clone the `GateContrib` repository with the command `git lfs clone https://github.com/OpenGATE/GateContrib.git`. If you omit the `lfs` from the `git clone` command then the large binary files may not be downloaded correctly.

[Gate](https://github.com/OpenGATE/Gate), based on [Geant4](https://geant4.web.cern.ch) library, allows to perform various Monte-Carlo simulations in the field of **medical physics**. [Gate](https://github.com/OpenGATE/Gate) can be used in numerous ways and for a lot of different applications. This repository contains [Gate](https://github.com/OpenGATE/Gate) simulation examples, mostly provided by users, in order to help sharing knowledge.


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

----
**If you encounter some problem while pulling:**  
The repository was rebased in October 2020. So you can face to pulling problems. You can try one of this solution:
 - If you do not have any modification in your local folder, you can remove and clone again the repository
 - If you do not want to remove your local folder, you can try `git reset --hard origin/master` to force the pull
 - For expert, you can try to rebase your local commits with the current master branch  

In any case, if you have some troubles, do not hesitate to send an issue via Github, we can help you.

