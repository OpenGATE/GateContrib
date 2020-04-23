# -*- coding: utf-8 -*-
"""
Analyse the data
"""

import pandas
import numpy as np 
import matplotlib.pyplot as plt
import getopt
import sys

opts, args = getopt.getopt(sys.argv[1:],"hi:o:",["ifile=","ofile="])
Area = float(args[0])**2
nPhotons = float(args[1])

#Area = 4.0**2
#nPhotons = 1e6

# Load energy spectrums
spectrum1 = pandas.read_csv(r'./Data/Spectrum1.txt', delimiter='\s+', 
                       header=0, names=('E', 'Fraction'))
spectrum2 = pandas.read_csv(r'./Data/Spectrum2.txt', delimiter='\s+', 
                       header=0, names=('E', 'Fraction'))

spectrum = pandas.concat([spectrum1, spectrum2], ignore_index=True)
spectrum['Fraction'] *= 0.5 * nPhotons / Area


data = pandas.read_csv(r'./output/detector_data.dat', skiprows=1, delimiter=' ', 
                       header=0, names=('E', 'Theta', 'Phi', 'Fluence'))

E = data['E'].to_numpy()
F = data['Fluence'].to_numpy()
plt.hist(E, weights=F, bins=50, label='Measured')
for i in range(4):
    if i == 0:
        plt.plot(spectrum['E'].to_numpy(), spectrum['Fraction'].to_numpy(),'ko', label='Expected')
    else:
        plt.plot(spectrum['E'].to_numpy(), spectrum['Fraction'].to_numpy(),'ko')

plt.legend()
plt.title('Energy spectrum')
plt.show()


plt.hist2d(data['Theta'],data['Phi'], bins=50, weights=data['Fluence'])
plt.xlabel('Theta [deg]')
plt.ylabel('Phi [deg]')
plt.show()







