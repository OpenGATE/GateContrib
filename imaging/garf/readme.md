
Example associated with:
Phys Med Biol. 2018 Oct 17;63(20):205013. doi: 10.1088/1361-6560/aae331. Learning SPECT detector angular response function with neural network for accelerating Monte-Carlo simulations. Sarrut D, Krah N, Badel JN, Létang JM. https://www.ncbi.nlm.nih.gov/pubmed/30238925

A method to speed up Monte-Carlo simulations of single photon emission computed tomography (SPECT) imaging is proposed. It uses an artificial neural network (ANN) to learn the angular response function (ARF) of a collimator-detector system. The ANN is trained once from a complete simulation including the complete detector head with collimator, crystal, and digitization process. In the simulation, particle tracking inside the SPECT head is replaced by a plane. Photons are stopped at the plane and the energy and direction are used as input to the ANN, which provides detection probabilities in each energy window. Compared to histogram-based ARF, the proposed method is less dependent on the statistics of the training data, provides similar simulation efficiency, and requires less training data. The implementation is available within the GATE platform.

# Installation

```pip install garf```

The source code is https://github.com/dsarrut/garf

The pypi project page is:  https://pypi.org/project/garf/


# Create the ARF model
## Generate the training dataset

First, run the simulation to generate the training dataset
```Gate mac/main_dataset.mac -a "[RADIONUCLIDE,Tc99m] [N,1e4]```
The output file is ```output/train.root```. 

Training dataset information may be displayed with (you must indicate the value for the Russian Roulette): 
```garf_plot_training_dataset output/train.root --rr 100```

## Train the neural network

Then train the NN with:
```garf_train config-nn.json output/train.root pth/arf.pth```

The output file ```output/arf.pth``` contains all ARF-NN data. 

Some information may be printed with:
```garf_nn_info pth/arf.pth```

An example of already computed neural network is the file ```arf.pth```.

# Use ARF-NN to perfom SPECT simulation
## Reference 'analog' simulation

An example of a reference image created from the conventional analog Monte-Carlo simulation:
```Gate mac/main_analog.mac -a '[RADIONUCLIDE,Lu177] [N,1e4] [SPECT_RADIUS,25]'```

The output image is ```output/projection.mhd```.

## Corresponding ARF simulation

(1) First you need to compile GATE with 'Torch_DIR'. See instruction here (FIXME). 

(2) Then convert the pth in a file format that can be read by Gate:

```garf_convert_pth_to_pt pth/arf_xRiI_v4.pth --no-gpu -v```

We advocate to not use the gpu first (computation time is not much improved). 

This command will create ```pth/arf_xRiI_v4.pt``` and ```pth/arf_xRiI_v4.json```, both files will be read by GATE. 

(3) Run the simulation:
```Gate mac/main_arf_v2.mac -a '[RADIONUCLIDE,Lu177] [N,1e5] [SPECT_RADIUS,25]'```

The output projection will be ```output/projection.mhd```. Image values are expressed in counts per events. You may want to scale the image according to the targeted number of events. **WARNING** if you merge results from several jobs, you need to take the mean not the sum of the counts (or divide by the number of jobs). 

The following tool read stat info from the reference simulation to get the targeted number of events. The -j option divide resulta by j, considering the results has been obtained with j jobs. The --noise flag add Poisson noise. 

```garf_scale output/projection.mhd --ref ref/stat.txt --noise -j 50```

It can be compared to the reference image with:
```garf_compare_image_profile output_reference_dataset/projection.mhd output/projection-s.mhd -w 10```

Compute associated uncertainty on the reference image:

```gate_image_uncertainty output_reference_dataset/projection.mhd -c -o uncert_ref.mhd -s -t 0.1 -e output_reference_dataset/projection/stats.txt```

In this command, the option ```-c```indicates that voxel's values are counts (integer). The uncertainty is the equal to the value (variance is equal to the mean). The option ```-t``` consider a 10% max threshold. Option ```-s``` compute results slice by slice. 

Compute associated uncertainty on the ARF generated image:

```gate_image_uncertainty output/projection.mhd -o uncert_arf.mhd -s -t 0.1 -e output/stats.txt```

ARF image is computed in counts/events, so you wan to scale this image according to a given number of events. This is done here with the option ```-n``` or with the valu read in the stat file. You don't need this option if image was scale previously.

Some pre-trained ARF neural networks are available in the ```data/pth``` folder.

# Reference data

The datasets that was used are available here: http://www.creatis.insa-lyon.fr/~dsarrut/garf

