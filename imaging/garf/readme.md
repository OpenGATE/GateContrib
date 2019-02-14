
Example associated with:
Phys Med Biol. 2018 Oct 17;63(20):205013. doi: 10.1088/1361-6560/aae331. Learning SPECT detector angular response function with neural network for accelerating Monte-Carlo simulations. Sarrut D, Krah N, Badel JN, Létang JM. https://www.ncbi.nlm.nih.gov/pubmed/30238925

A method to speed up Monte-Carlo simulations of single photon emission computed tomography (SPECT) imaging is proposed. It uses an artificial neural network (ANN) to learn the angular response function (ARF) of a collimator-detector system. The ANN is trained once from a complete simulation including the complete detector head with collimator, crystal, and digitization process. In the simulation, particle tracking inside the SPECT head is replaced by a plane. Photons are stopped at the plane and the energy and direction are used as input to the ANN, which provides detection probabilities in each energy window. Compared to histogram-based ARF, the proposed method is less dependent on the statistics of the training data, provides similar simulation efficiency, and requires less training data. The implementation is available within the GATE platform.

# Installation

```pip install garf```

The source code is here: https://github.com/dsarrut/garf

# Create the ARF model

## Generate the training dataset

First, run the simulation to generate the training dataset
```Gate mac/main_training_dataset.mac```
The output file is ```output/train.root```. 

Training dataset information may be displayed with: 
```garf_plot_training_dataset output/train.root```

An example of already computed dataset is given in the folder ```output_training_dataset```.

## Train the neural network

Then train the NN with:
```garf_train config-nn.json output/train.root pth/arf.pth```

The output file is ```output/arf.pth```, it contains all ARF-NN data. 

Some information may be printed with:
```garf_nn_info pth/arf.pth```

An example of already computed neural network is the file ```arf.pth```.

# Use ARF-NN to perfom SPECT simulation

## Generate a reference 'analog' simulation

Create a reference image from the conventional analog Monte-Carlo simulation:
```Gate mac/main_analog.mac```

The output image is ```output/projection.mhd```.

An example of already computed image is in ```output_reference_dataset``` (about 2e10 particles).


## ARF simulation

Create the dataset that will be used by the ARF (short simulation):
```Gate mac/main_arf.mac```

The output dataset is ```output/test.root```

An example of already computed dataset is in ```output_arf_dataset``` (about 5e8 particles).

Create the final image using the ARF-NN with: 
```garf_build_arf_image_with_nn -b 1e5 output_arf_dataset/test.root 47342387 arf.pth output/projection_arf.mhd```

The option -b should be adapted according to your gpu card memory (large value is faster but may lead to 'out of memory').

Output image is ```output/projection_arf```. 

Scale the image to the same number of events than the reference image and add Poisson noise:
```garf_scale_and_Poisson_noise output/projection_arf.mhd 18837052666 output/projection_arf_final.mhd```

It can be compared to the reference image with:
```garf_compare_image_profile output_reference_dataset/projection.mhd output/projection_arf_final.mhd -w 10```

## external data

The folders: 
```output_training_dataset```
```output_reference_dataset```
```output_arf_dataset```
are available here: http://www.creatis.insa-lyon.fr/~dsarrut/garf



