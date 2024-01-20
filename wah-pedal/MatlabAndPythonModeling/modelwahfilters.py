#%%

### Setup ###

# modelwahfilters.py
# Model measured magnitude transfer functions from wah pedal with peaking filters

import numpy as np
import matplotlib.pyplot as plt
import scipy.signal as sig
from scipy.io import loadmat

# scipy's signal.bilinear says no prewarping is done, so here's this function that ~should~ work:

def bilinearwarp(b, a, fs, w0):
    # like scipy's signal.bilinear, but with frequency warping
    # expects a second-order filter i.e. b and a are arrays of size 3
    K = w0/np.tan(w0/(2*fs));
    Ksq = np.power(K, 2);
    b0 = b[0]*Ksq;
    b1 = b[1]*K;
    b2 = b[2];
    a0 = a[0]*Ksq;
    a1 = a[1]*K;
    a2 = a[2];
    norm = 1/(a0+a1+a2);
    bz0 = (b0+b1+b2)*norm;
    bz1 = 2*(b2-b0)*norm;
    bz2 = (b0-b1+b2)*norm;
    az1 = 2*(a2-a0)*norm;
    az2 = (a0-a1+a2)*norm;
    return [[bz0, bz1, bz2], [1, az1, az2]];

#%%

### Get Data from MATLAB ###

# Load wahtransferfunctions.mat
matlab = loadmat( "wahtransferfunctions.mat" );

# wahtransferfunctions.mat includes the following variables:
# tfs   % Frequency responses (FFTs) of 11 wah pedal settings
# fs    % Sampling rate at which measurements were made (44.1k)
# pedal % Vector containing pedal positions at which measurements were made
# freq  % Vector of frequencies at which responses were measured

tfs = np.transpose(matlab['tfs']);
fs = matlab['fs'][0][0];
pedal = matlab['pedal'][0];
freq = matlab['freq'][0];

measurementnumber = 0;
pedalposition = pedal[measurementnumber];

#%%

### Filter Math ###

# Peaking filter definition 
# 
# 
#                gamma*s/w0
#  H(s) = __________________________
#          s^2/w0^2 + s/(w0*Q) + 1
# 

# Choose gamma, f0, Q to match each of the 11 wah pedal responses.
gamma = 0.25;            # gamma*Q = peak gain
f0 = 1000;               # f0 = center freq, Hz
w0 = f0*2*np.pi;         # w0 in radians/sec
Q = 8.0;                 # Q = resonance

b = [0, gamma/w0, 0];
a = [np.power(w0, -2), 1/(w0*Q), 1];

# Option 1
[bz, az] = sig.bilinear(b, a, fs);  # Bilinear transform for sampling rate fs,
wz, H = sig.freqz(bz, az, 8192);    # Calculate response of digital filter

# option 2
[bz_warp, az_warp] = bilinearwarp(b, a, fs, w0);  # Bilinear transform for sampling rate fs,
wz_warp, H_warp = sig.freqz(bz_warp, az_warp, 8192);    # Calculate response of digital filter

#%%

### Plotting ###

# Plot dB response of pedal at measured position (measurementnumber):
# 11 positions measured, so measurementnumber must be between 0, 10.
# ***NOTE THAT THE RESPONSE DOES NOT CHANGE FOR THE FIRST SEVERAL PEDAL POSITIONS MEASURED!!***

plt.figure(1)
plt.plot(freq, 20*np.log10(np.abs(tfs[measurementnumber])), 'b-', linewidth = 2, label = "Measured")
plt.plot(wz*fs/(2*np.pi), 20*np.log10(np.abs(H)), 'r-', linewidth = 2, label = "Model, no pre-warping")
plt.plot(wz_warp*fs/(2*np.pi), 20*np.log10(np.abs(H_warp)), 'g--', linewidth = 2, label = "Model, pre-warping")
plt.grid(1, which='both')
plt.xscale("log")
plt.xlim([20, 20000]); # Limit axes to 20-20k Hz
plt.ylim([-40, 10]); 
plt.xlabel('Frequency, Hz')
plt.ylabel('Magnitude Response, dB')
plt.legend()
plt.title('Pedal Position='+str(pedalposition))
plt.show()
# %%
