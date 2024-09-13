import matplotlib
matplotlib.get_backend()
matplotlib.use("TkAgg")
import matplotlib as mpl
import matplotlib.pyplot as plt # Graphic library
import numpy as np # Data manipulaion
import math as m
import uproot
import math


from dataclasses import dataclass




@dataclass
class Cone:
    x1: float =0.0
    y1: float =0.0
    z1: float =0.0
    x2: float =0.0
    y2: float =0.0
    z2: float =0.0
    E1: float =0.0
    ER: float =0.0



class Hist1D(object):

    def __init__(self, nbins, xlow, xhigh):
        self.nbins = nbins
        self.xlow  = xlow
        self.xhigh = xhigh
        self.hist, edges = np.histogram([], bins=nbins, range=(xlow, xhigh))
        self.bins = (edges[:-1] + edges[1:]) / 2.

    def fill(self, arr):
        hist, edges = np.histogram(arr, bins=self.nbins, range=(self.xlow, self.xhigh))
        self.hist += hist

    @property
    def data(self):
        return self.bins, self.hist



colors = ['r', 'b','g','c','m','y','k' ]
markers=['o','v','^','s','x','d','+','*','h']


#path='/Users/etxebeste/gateworkdir/GateContrib/imaging/ComptonCamera/output/adder/'
#path='/Users/etxebeste/gateworkdir/GateContrib/imaging/ComptonCamera/output/clustering/'
path='/Users/etxebeste/gateworkdir/GateContrib/imaging/ComptonCamera/output/ideal/'


#nameSeqCoin="CC_adder_sequenceCoincidence.root"
#nameSeqCoin="CC_clustering_sequenceCoincidence.root"
nameSeqCoin="CC_idealprocessing_sequenceCoincidence.root"


file_SeqCoinc= uproot.open(path+nameSeqCoin)

IsIdealdata=True

#================================================================
#------load seq coincidences-----------------------------
pSeqCoincidence = file_SeqCoinc['sequenceCoincidence']
arrays=pSeqCoincidence.arrays(
    ['coincID', 'eventID', 'energy', 'globalPosZ', 'globalPosX', 'globalPosY', 'energyIni', 'energyFinal'])
coincID_SeqCoinc=arrays['coincID']
evtID_SeqCoinc=arrays['eventID']
edep_SeqCoinc=arrays['energy']*1000#keV
posZ_SeqCoinc=arrays['globalPosZ']
posX_SeqCoinc=arrays['globalPosX']
posY_SeqCoinc=arrays['globalPosY']
Eini_SeqCoinc=[]
EFin_SeqCoinc=[]
if IsIdealdata==True:
    print("Ideal data selected")
    Eini_SeqCoinc=arrays['energyIni']*1000#keV
    EFin_SeqCoinc=arrays['energyFinal']*1000#keV

Emin=0#keV
Emax=800#keV
nbinsE=200#

binSz=0.002
maxAngle=0.5#rad
nbins=int(1.0/0.002)#500 bins

hist_ARM= Hist1D(nbins, (-1)*maxAngle, maxAngle)

Esource=662#
sourcePosZ=0

uniqueCoincIDv, uniqueCoincIDindex, uniqueCoincIDcounts =np.unique(coincID_SeqCoinc, return_index=True,  return_counts=True)
print("len unique coindID", len(uniqueCoincIDv))

E1=[]
ER=[]
for j in range(0, len(uniqueCoincIDindex)):
    #For each different coincidence
    aCone=Cone()
    edepTot=0
    if IsIdealdata==True:
         aCone.x1=posX_SeqCoinc[uniqueCoincIDindex[j]]
         aCone.y1=posY_SeqCoinc[uniqueCoincIDindex[j]]
         aCone.z1=posZ_SeqCoinc[uniqueCoincIDindex[j]]
         aCone.E1=(Eini_SeqCoinc[uniqueCoincIDindex[j]]-EFin_SeqCoinc[uniqueCoincIDindex[j]]);
         aCone.ER=EFin_SeqCoinc[uniqueCoincIDindex[j]]
         aCone.x2=posX_SeqCoinc[uniqueCoincIDindex[j]+1]
         aCone.y2=posY_SeqCoinc[uniqueCoincIDindex[j]+1]
         aCone.z2=posZ_SeqCoinc[uniqueCoincIDindex[j]+1]
         E1.append(aCone.E1)
         ER.append(aCone.ER)
    else:
        for i in range (0, uniqueCoincIDcounts[j]):
            if i==0:
                aCone.x1=posX_SeqCoinc[uniqueCoincIDindex[j]+i]
                aCone.y1=posY_SeqCoinc[uniqueCoincIDindex[j]+i]
                aCone.z1=posZ_SeqCoinc[uniqueCoincIDindex[j]+i]
                aCone.E1=edep_SeqCoinc[uniqueCoincIDindex[j]+i]
                E1.append(aCone.E1)
            if i==1:
                aCone.x2=posX_SeqCoinc[uniqueCoincIDindex[j]+i]
                aCone.y2=posY_SeqCoinc[uniqueCoincIDindex[j]+i]
                aCone.z2=posZ_SeqCoinc[uniqueCoincIDindex[j]+i]

            edepTot+=edep_SeqCoinc[uniqueCoincIDindex[j]+i]
        aCone.ER=edepTot-aCone.E1
        ER.append(aCone.ER)






ESum=[x + y for x, y in zip(E1, ER)]
E1=np.asarray(E1, dtype=np.float32)
ER=np.asarray(ER, dtype=np.float32)
ESum=np.asarray(ESum, dtype=np.float32)


fig = plt.figure()
plt.hist(E1, bins=nbinsE,range=(Emin,Emax), histtype='step',lw=2,color='r',label='E1')
plt.hist(ER, bins=nbinsE,range=(Emin,Emax), histtype='step',lw=2,color='b',label='ER')
plt.hist(ESum, bins=nbinsE,range=(Emin,Emax), histtype='step',lw=2,color='k',label='ESum')
plt.xlabel("E (keV)", fontsize=12)
plt.legend()
plt.savefig(path+"E.png", bbox_inches="tight", facecolor='white', edgecolor='none')



fig2 = plt.figure()
plt.hist2d(E1, ER, bins=(nbinsE, nbinsE),range=((Emin,Emax),(Emin,Emax)), cmap=plt.cm.jet)
plt.xlabel("E1 (keV)", fontsize=12)
plt.ylabel("ER (keV)", fontsize=12)
plt.savefig(path+"E1_ER.png", bbox_inches="tight", facecolor='white', edgecolor='none')




fig2_ = plt.figure()
plt.hist(ER, bins=nbins,range=(Emin,Emax),histtype='step',lw='2',color='b')
plt.xlabel("ER (keV)", fontsize=12)
plt.savefig(path+"ER.png", bbox_inches="tight", facecolor='white', edgecolor='none')

mu = E1.mean()
median = np.median(E1)
sigma = E1.std()
textstr = '\n'.join((
    r'$\mu=%.2f$' % (mu, ),
    r'$\mathrm{median}=%.2f$' % (median, ),
    r'$\sigma=%.2f$' % (sigma, )))
fig, ax = plt.subplots()
plt.hist(E1, bins=nbinsE,range=(Emin,Emax), histtype='step',lw=2,color='r')
plt.xlabel("E1 (keV)", fontsize=12)
props = dict(boxstyle='round', facecolor='wheat', alpha=0.5)
ax.text(0.65, 0.95, textstr, transform=ax.transAxes, fontsize=14,
        verticalalignment='top', bbox=props)
plt.savefig(path+"E1.png", bbox_inches="tight", facecolor='white', edgecolor='none')


mu = ESum.mean()
median = np.median(ESum)
sigma = ESum.std()
textstr = '\n'.join((
    r'$\mu=%.2f$' % (mu, ),
    r'$\mathrm{median}=%.2f$' % (median, ),
    r'$\sigma=%.2f$' % (sigma, )))
fig, ax = plt.subplots()
plt.hist(ESum, bins=nbinsE,range=(Emin,Emax), histtype='step',lw=2,color='k')
plt.xlabel(r'$E_{sum}$ (keV)', fontsize=12)
props = dict(boxstyle='round', facecolor='wheat', alpha=0.5)
ax.text(0.05, 0.95, textstr, transform=ax.transAxes, fontsize=14,
        verticalalignment='top', bbox=props)
plt.savefig(path+"ESum.png", bbox_inches="tight", facecolor='white', edgecolor='none')

