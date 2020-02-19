##################################################
## Goal of this script is to compare old root system output
# defined in https://opengate.readthedocs.io/en/latest/data_output_management.html#root-output
# and the new one: https://opengate.readthedocs.io/en/latest/data_output_management.html#new-unified-tree-output-root-numpy-and-more
##################################################
## Author: Mathieu Dupont
## Email: mdupont@cppm.in2p3.fr
##################################################


import uproot
import numpy as np


class color:
   PURPLE = '\033[95m'
   CYAN = '\033[96m'
   DARKCYAN = '\033[36m'
   BLUE = '\033[94m'
   GREEN = '\033[92m'
   YELLOW = '\033[93m'
   RED = '\033[91m'
   BOLD = '\033[1m'
   UNDERLINE = '\033[4m'
   END = '\033[0m'


def compare_two_array(a, b):
    for key in a.dtype.fields.keys():
        print("\t", key, end=" ")
        if key not in b.dtype.fields.keys():
            print("\t\tno ", key, "in new array")
            continue
        if len(a[key]) != len(b[key]):
            raise ValueError("Not same size ! ")
        if a[key].dtype == np.float64 or a[key].dtype == np.float32:
            bb = b[key].astype(np.float32)
            if not np.allclose(a[key], bb, atol=1e-8):
                raise ValueError(f"\n{key} are different")
            else:
                print("are identical", end="")
        else:
            if not np.all(np.equal(a[key], b[key])):
                raise ValueError(f"\n{key} are different")
            else:
                print("are identical", end="")

        if a[key].dtype != b[key].dtype:
            print("\t\t\t(warning mismatch ", a[key].dtype, " != ", b[key].dtype, ")")
        else:
            print("")#force end of line


if __name__ == '__main__':



    old_system = {}
    root = uproot.open("output/data_PET.root")
    old_system['Coincidences'] = root['Coincidences'].pandas.df().to_records()
    old_system['Singles'] = root['Singles'].pandas.df().to_records()
    old_system['Hits'] = root['Hits'].pandas.df().to_records()
    old_system['LESingles'] = root['LESingles'].pandas.df().to_records()

    new_root_system = {}

    new_root_system['Coincidences'] = uproot.open("output/data_PET.Coincidences.root")['tree'].pandas.df().to_records()
    new_root_system['Singles'] = uproot.open("output/data_PET.Singles.root")['tree'].pandas.df().to_records()
    new_root_system['Hits'] = uproot.open("output/data_PET.hits.root")['tree'].pandas.df().to_records()
    new_root_system['LESingles'] = uproot.open("output/data_PET.LESingles.root")['tree'].pandas.df().to_records()

    numpy_system = {}
    numpy_system['Coincidences'] = np.load("output/data_PET.Coincidences.npy")
    numpy_system['Singles'] = np.load("output/data_PET.Singles.npy")
    numpy_system['Hits'] = np.load("output/data_PET.hits.npy")
    numpy_system['LESingles'] = np.load("output/data_PET.LESingles.npy")


    # ascii_system = {}
    # ascii_system['Hits'] = pandas.read_csv('output/data_PET.hits.txt').to_records()
    # ascii_system['Coincidences'] = pandas.read_csv('output/data_PET.Coincidences.txt').to_records()
    # ascii_system['Singles'] = pandas.read_csv('output/data_PET.Singles.txt').to_records()


    for output in ['Coincidences', 'Singles', 'Hits', 'LESingles']:
        print(color.BOLD, "Check output betwwen old ROOT and new ROOT for:", output, color.END)
        compare_two_array(old_system[output], new_root_system[output])
        print(color.BOLD, "Check output betwwen old ROOT and new numpy for:", output, color.END)
        compare_two_array(old_system[output], numpy_system[output])
        # print(color.BOLD, "Check output betwwen old ROOT and new ascii for:", output, color.END)
        # compare_two_array(old_system[output], ascii_system[output])










