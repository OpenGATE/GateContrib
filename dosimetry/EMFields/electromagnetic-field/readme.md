**Description:** Example of a 1 MeV proton beam inside an uniform electromagnetic field of  40 kV/m and 1.5 T in vacuum. The electromagnetic field is defined in data/emfield.txt. The purpose of this example is to demonstrate the basic functionality of the command:

```
/gate/geometry/setElectMagTabulateField3D
```

which can be used to apply custom uniform or non-uniform electromagnetic fields in GATE. The post-processing script plots the beam deflection curve based on Gaussian fits of the 2D dose distribution scored at 0.1 mm distances.

**Author:** Haberl D. 

**Date:** 2021-03-20

**Version:** Gate v9.0-dev, Geant4.10.07.p01, ROOT v6.20.02

**Usage:** 
```
Gate mac/main.mac

python post-processing.py
````

**Input:**
- data/emfield.txt
- data/GateMaterials.db

**Output:**
- output/doseInXZ-Dose.txt
- output/doseInYZ-Dose.txt
- output/statistics.txt