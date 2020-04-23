Goal of this example is to illustrate new GateToTree output, as described in [here in the docs](https://opengate.readthedocs.io/en/latest/data_output_management.html#new-unified-tree-output-root-numpy-and-more)
 and not to provide a realistic PET system. 

To run this example: `Gate PET_CylindricalPET_System.mac`

Output data will go in `output` folder. 

The python script provided `compare_old_and_new_output.py` permits to compare old ROOT 
output system with new system (ROOT and numpy output). It will compare each columns, 
row by row for the following outputs: 'Coincidences', 'Singles', 'Hits', 'LESingles'. A 
exception is raised in case of different data.  

To run the script, `uproot and numpy` python modules have to be installed.

`python compare_old_and_new_output.py`

TODO: GateToTree is able to write Ascii data, but as types information of variables are not stored, 
the comparison function has to be adapted.

  





