
**Author**: Simon Kirchhof (simonkirchhof@outlook.de)

**Usage**: 
```
$ Gate mac/main.mac
```


## Information

GATE example which shows the construction of a tetrahedral-mesh geometry. The input file type (`.ele`) can be generated using the open-source tool [TetGen](http://www.tetgen.org). Furthermore, it shows the functionality of a dose actor interface specific to tetrahedral-mesh geometries.


## Inputs

Two of the input files are based on an example from the [TetGen homepage](http://wias-berlin.de/software/tetgen/1.5/fformats.examples.html):
* `data/BodyHasHeart.ele`
* `data/BodyHasHeart.node`

The material data base is the GATE default:
* `data/GateMaterials.db`

The region attribute table `data/RegionAttributeTable.dat` is necessary, to assign materials to each tetrahedron, based on the region-IDs defined in the `.ele` file. 


## Outputs

A csv-table of the dose scored in each tetrahedron.
