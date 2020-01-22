#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import numpy as np
import sys
import os
import re
import click
from matplotlib import pyplot as plt
import SimpleITK as sitk
import scipy
#from sklearn.gaussian_process import GaussianProcess

def read_images(folder, scale):
    print(folder)
    f = os.path.join(folder, 'dose-Edep.mhd')
    img = sitk.ReadImage(f)    
    data = sitk.GetArrayFromImage(img)
    data = data*scale
    
    f = os.path.join(folder, 'dose-Edep-Uncertainty.mhd')
    img_s = sitk.ReadImage(f)
    data_s = sitk.GetArrayFromImage(img_s)

    return img, data, data_s

CONTEXT_SETTINGS = dict(help_option_names=['-h', '--help'])
@click.command(context_settings=CONTEXT_SETTINGS)
@click.argument('folders', nargs=3)
@click.option('--scale', '-s', multiple=True)
@click.option('--imax', '-m', multiple=True)
@click.option('--factor', '-f', default = '0.01')
def relative_uncertainty(folders, imax, scale, factor):
    '''
    \b
    TODO
    '''

    img1, data1, uncert1 = read_images(folders[0], float(scale[0]))
    img2, data2, uncert2 = read_images(folders[1], float(scale[1]))
    img3, data3, uncert3 = read_images(folders[2], float(scale[2]))

    myfontsize = 22
    myfontsize_tic = 17
    myfontsize_title = 17
    
    # param
    f = float(factor) # 0.05
    nb_sig = 3

    # detect the max with quantile to be a bit more robust
    mask = np.ones_like(data1)
    mi = np.amin(data1[mask==1])
    ma = np.amax(data1[mask==1])
    mean = np.mean(data1[mask==1])
    med = np.median(data1[mask==1])
    print('Data1: min max mean med', mi, ma, mean, med) 
    q = np.amax(data1)
    print('Data1 max = ', q)
    q = np.quantile(data1, 0.99999)
    print('Data1 maxQ = ', q)
    mask = np.where(data1<q*f, 0, mask)
    
    mi = np.amin(data1[mask==1])
    ma = np.amax(data1[mask==1])
    mean = np.mean(data1[mask==1])
    med = np.median(data1[mask==1])
    print('Data1 min max mean med', mi, ma, mean, med)

    # save mask
    img = sitk.GetImageFromArray(mask)
    img.CopyInformation(img1)
    sitk.WriteImage(img, 'mask.mhd')
    print('Length = ', len(data1), len(data2), len(data3))
    
    # compute uncert
    uncert1 = uncert1*data1
    uncert2 = uncert2*data2
    uncert3 = uncert3*data3    

    # compute sigma
    sigma1 = np.sqrt(uncert1*uncert1+uncert2*uncert2)
    sigma2 = np.sqrt(uncert1*uncert1+uncert3*uncert3)
    sigma1 = sigma1[mask==1]
    sigma2 = sigma2[mask==1]
    
    # compute relative difference
    def compute_diff(data1, data2):
        diff = (data1 - data2)# /data1
        print('diff min max', np.amin(diff), np.amax(diff))
        return diff

    d1 = data1[mask==1]
    d2 = data2[mask==1]
    d3 = data3[mask==1]
    #diff1 = compute_diff(d1, d2)/np.mean(d1)
    #diff2 = compute_diff(d1, d3)/np.mean(d1)
    amax = np.quantile(d1, 0.999)
    print('Max value', amax)
    amean = np.mean(d1)
    amean = amax
    diff1 = compute_diff(d1, d2)/amean
    diff2 = compute_diff(d1, d3)/amean

    print('Length data  =', len(d1), len(d2), len(d3))
    print('Length sigma =', len(sigma1), len(sigma2))
    u1 = uncert1[mask == 1]
    u2 = uncert2[mask == 1]
    u3 = uncert3[mask == 1]
    print('Mean uncert {}% {}% {}%'.format(np.mean(u1)*100,
                                           np.mean(u2)*100,
                                           np.mean(u3)*100))
    print('Mean sigma  {}% {}%'.format(np.mean(sigma1)/np.mean(d1),
                                       np.mean(sigma2)/np.mean(d1)))

    # plot histo
    fig, ax = plt.subplots(1, 2, figsize=(15,8)) 
    fs = myfontsize 
    a = ax[0]
    q1 = np.quantile(diff1, 0.01)
    q2 = np.quantile(diff1, 0.99)
    print('Quantile for H', q1,q2)
    l1 = '{:15s} $\mu=${:.2f}% '.format('PHSP1 vs PHSP2', np.mean(diff1)*100.0)#, np.mean(sigma1)/np.mean(d1)*100.0)
    l2 = '{:15s} $\mu=${:.2f}% '.format('PHSP1 vs GAN', np.mean(diff2)*100.0)#, np.mean(sigma2)/np.mean(d1)*100.0)
    print(l1)
    print(l2)
    if (folders[1] != folders[2]):
        a.hist(diff1, 200, range=(q1, q2),
               density=False, facecolor='g', alpha=0.3,
               label=l1)
    a.hist(diff2, 200, range=(q1, q2),
           density=False, facecolor='b', alpha=0.3,
           label=l2)
    #a.legend(prop={'family':'monospace', 'size': 10})
    a.legend(loc='center left', prop={'size': myfontsize_title})
    vals = a.get_xticks()
    a.set_xticklabels(['{:,.1%}'.format(x) for x in vals])
    x1 = np.mean(diff1)
    a.axvline(x=x1, color='k') 
    x2 = np.mean(diff2)
    a.axvline(x=x2, color='r')
    a.set_xlabel('Difference %', fontsize=fs)
    a.set_ylabel('Counts', fontsize=fs)
    a.tick_params(labelsize=myfontsize_tic)
    print('----> PHSP1 vs PHSP2 mean diff1 = ', x1*100.0)
    print('----> PHSP1 vs GAN   mean diff2 = ', x2*100.0)
    
    a = ax[1]
    x = (d1-d2)/sigma1
    y = (d1-d3)/sigma2
    l1 = '{:} $\mu=${:.2f} $\sigma=${:.2f}'.format('PHSP1 vs PHSP2', np.mean(x), np.std(x))
    l2 = '{:} $\mu=${:.2f} $\sigma=${:.2f}'.format('PHSP1 vs GAN', np.mean(y), np.std(y))
    print(l1)
    print(l2)
    a.hist(x, 200, range=(-3, 3),
           density=False, facecolor='g', alpha=0.3,
           label=l1)
    a.hist(y, 200, range=(-3, 3),
           density=False, facecolor='b', alpha=0.3,
           label=l2)
    print('PHSP1 vs PHSP2 mu et sigma = ', np.mean(x), np.std(x))
    print('PHSP1 vs GAN mu et sigma = ', np.mean(y), np.std(y))
    vals = a.get_xticks()
    a.set_xlabel('Nb of sigma', fontsize=fs)
    a.set_ylabel('Counts', fontsize=fs)
    a.tick_params(labelsize=myfontsize_tic)
    #a.legend(prop={'family':'monospace', 'size': 10})
    a.legend(loc='center left', prop={'size': myfontsize_title})

    # tics in %
    # vals = a.get_xticks()
    # a.set_xticklabels(['{:,.0%}'.format(x) for x in vals])


    # a = ax[2]
    # a.plot(d1, d2, 'r.')
    # a.plot(d1, d3, 'b.')
    # a.plot(d1, d1, 'k-')
    #a.legend(prop={'size': 16})
    
    # #a.axvline(x=np.mean(sigma1)*100.0, color='k')
    # x = np.mean(sigma2)
    # a.axvline(x=x, color='k')
    # ylim = a.get_ylim()
    # plt.text(x*1.5, 0.25*ylim[1], 'mean $\sigma$ = {0:.1f}%'.format(x*100.0),rotation=90, fontsize=16)

    # x = np.mean(diff1)
    # a.axvline(x=x, color='g')
    # plt.text(x*1.5, 0.65*ylim[1], 'mean diff1 = {0:.1f}%'.format(x*100.0),rotation=90, color='g', fontsize=16)

    # x = np.mean(diff2)
    # a.axvline(x=x, color='r')
    # plt.text(x*1.2, 0.25*ylim[1], 'mean diff2 = {0:.1f}%'.format(x*100.0),rotation=90, color='r', fontsize=16)

    # x = np.mean(diff1/diff1-1.0)
    # print(x, x.shape)
    # a.axvline(x=x, color='k')
    
    
    img = sitk.GetImageFromArray((data1-data2)/np.mean(d1))
    img.CopyInformation(img1)
    sitk.WriteImage(img, 'diff1.mhd')
    
    img = sitk.GetImageFromArray((data1-data3)/np.mean(d1))
    img.CopyInformation(img1)
    sitk.WriteImage(img, 'diff2.mhd')
    
    plt.tight_layout()
    s = ''+folders[2]
    # plt.suptitle(s) # FIXME TO REMOVE
    plt.savefig('a.pdf', dpi=fig.dpi)
    plt.show()

# --------------------------------------------------------------------------
if __name__ == '__main__':
    relative_uncertainty()

