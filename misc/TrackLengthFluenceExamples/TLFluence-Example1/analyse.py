import SimpleITK as sitk
import numpy as np
import matplotlib.pyplot as plt
import getopt
import sys

'''
This funciton reads a '.mhd' file using SimpleITK and return the image array, origin and spacing of the image.
'''

def load_itk(filename):
    # Reads the image using SimpleITK
    itkimage = sitk.ReadImage(filename)

    # Convert the image to a  numpy array first and then shuffle the dimensions to get axis in the order z,y,x
    ct_scan = sitk.GetArrayFromImage(itkimage)

    # Read the origin of the ct_scan, will be used to convert the coordinates from world to voxel and vice versa.
    origin = np.array(list(reversed(itkimage.GetOrigin())))

    # Read the spacing along each dimension
    spacing = np.array(list(reversed(itkimage.GetSpacing())))

    return ct_scan, origin, spacing



opts, args = getopt.getopt(sys.argv[1:],"hi:o:",["ifile=","ofile="])
Area = float(args[0])**2
nPhotons = float(args[1])
	
	



arr = load_itk("output/detector-Fluence.mhd")
arr_std = load_itk("output/detector-Fluence-Uncertainty.mhd")
mu_Theory = nPhotons/Area;
std_Meas = np.std(arr[0].flatten());
std_MC = np.mean(arr_std[0].flatten())
mu = np.mean(arr[0].flatten());

plt.hist(arr[0].flatten(), normed = False, bins=10)
plt.ylabel('Number of pixels');
plt.title(r'MC='+str(mu)+r'$\pm$'+str(mu*std_MC)+r'$ cm^{-2}$, Expected ='+str(mu_Theory)+r'$\pm$'+str(std_Meas)+r'$ cm^{-2}$')
plt.grid(True)
plt.show()




