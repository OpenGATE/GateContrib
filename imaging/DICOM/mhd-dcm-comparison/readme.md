Author:
 - Thomas DESCHLER (thomas@deschler.fr)

DICOM Series provided by:
 - Jérôme Suhard (jerome@suhard.fr)

Note that DICOM series are provided as a tar.gz archive. Before running the example, you have to decompress this file:
* `cd PATH_TO/imaging/DICOM/mhd-dcm-comparison/data`<br>
* `tar -xzf dataDICOM.tar.gz`

### Informations:
  * The main simulation files are constructed as follows : `main-[series name]-[input format].mac`<br>
    `[series name] : ffp, ffs, hfp, hfs`<br>
    `[input format]: mhd, dcm`<br>
  * Each main file will generate two mhd images:
    * one containing the density dump of the image (`density-[series name]-[input format].mhd/.raw`)
    * one containing the deposited dose in the image (`DA-[series name]-[input format]-Dose.mhd/.raw`)
  * Comparison between input formats can be made by the diff command:<br>
      `diff DA-[seriesA]-mhd-Dose.raw DA-[seriesA]-dcm-Dose.raw`
