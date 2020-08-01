import numpy as np
from matplotlib import pyplot as plt

x = np.arange(0,3*np.pi,0.1)
y = np.sin(x)
y2 = np.cos(x)

plt.subplot(2,1,1)
plt.plot(x,y)
plt.title('Sine')

plt.subplot(2,1,2)
plt.plot(x,y2)
plt.title('Cosine')

plt.show()