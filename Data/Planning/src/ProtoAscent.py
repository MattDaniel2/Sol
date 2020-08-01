import numpy as np
from matplotlib import pyplot as plt

### 4 Phases -- Initial Ascent, Max Q, Final Ascent, Level-Off ###
e_alt   = 50000
s_alt   = 100
mq_alt  = 16000
mq_rad  = 2000
vh_alt  = np.arange(s_alt,e_alt,10)


#### First Pass Sqrt of Normalized Difference in Vehicle Altitude and End Altitude ###
dphi = 90.0 - (90.0 * np.sqrt((1.0*vh_alt - s_alt)/(e_alt-s_alt)))
#dphi_mq = dphi_ia[-1]
#dphi_fa = 90.0 - (90.0 * np.sqrt(np.abs(vh_alt[(mq_alt+mq_rad):] - e_alt)/(e_alt - s_alt)))
#dphi_lo = 90.0 * np.arange(e_alt, 75000, 10)
#dphi = np.arange(s_alt, e_alt, 10)

#np.concatenate(dphi_ia, dphi_fa, dphi)

plt.subplot(3,1,1)
plt.xlabel("Vehicle Altitude (m)")
plt.ylabel("Delta Phi (deg)")
plt.title("Pitch Diff = Sqrt(Alt)")
plt.plot(vh_alt,dphi)
plt.show()

### Second Pass E^(x)