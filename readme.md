**GateContrib**

*(Warning: this is yet a tentative & experimental Gate sub-project. Contributions and suggestions welcome)*

[Gate](https://github.com/OpenGATE/Gate), based on [Geant4](https://geant4.web.cern.ch) library, allows to perform various Monte-Carlo simulations in the field of **medical physics**. [Gate](https://github.com/OpenGATE/Gate) can be used in numerous ways and for a lot of different applications. This repository contains [Gate](https://github.com/OpenGATE/Gate) simulation examples, mostly provided by users, in order to help sharing knowledge.

*Warning* - This repository contains data (binary files), stored with [git-lfs](https://git-lfs.github.com/) extension. Find below a step-by-step tutorial to install git-lfs:

1. Download the [Git LFS extension](https://github.com/git-lfs/git-lfs/releases/download/v2.0.1/git-lfs-linux-amd64-2.0.1.tar.gz) for versioning large files
2. Untar, install and set up the Git command line extension<br>
<code>tar -xzf git-lfs-linux-amd64-2.0.1.tar.gz</code><br>
<code>cd git-lfs-2.0.1</code><br>
<code>sudo ./install.sh</code><br>
If your installation was succesful, your terminal should display the following message:<br>
<code>Git LFS initialized</code><br>
Note that you only have to set up Git LFS once. 
3) Clone the Gate user-oriented repository as usual<br>
<code>git clone https://github.com/OpenGATE/GateContrib.git</code><br>
Note that the <code>git lfs clone https://github.com/OpenGATE/GateContrib.git</code> command operates exactly like <code>git clone</code> and takes all the same arguments, but has one important difference: it's a lot faster! Depending on the number of files you have it can be more than 10x faster in fact.<br>
The output of the executing commande should be:<br>
<code>Cloning into 'GateContrib'...</code><br>
<code>remote: Counting objects: 21076, done.</code><br>
<code>remote: Compressing objects: 100% (61/61), done.</code><br>
<code>remote: Total 21076 (delta 36), reused 0 (delta 0), pack-reused 21012</code><br>
<code>Receiving objects: 100% (21076/21076), 13.96 MiB | 3.76 MiB/s, done.</code><br>
<code>Resolving deltas: 100% (14211/14211), done.</code><br> 
<code>Checking connectivity... done.</code><br>
<code>Downloading dosimetry/Radiotherapy/example10/data/phantom.raw (3.25 MB)</code><br>
<code>Downloading dosimetry/Radiotherapy/example2/data/patient-2mm.raw (3.36 MB)</code><br>
<code>...</code><br>
<code>Checking out files: 100% (549/549), done.</code><br>
 
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

