import numpy as np
import matplotlib.pyplot as plt

file = np.genfromtxt('RadialVelocities.dat', skip_header = 1)
r = file[:,0]
v = file[:,1]

plt.scatter(r,v)
plt.xlabel('Radio (kpc)')
plt.ylabel('Velocidad (km/s)')
plt.title('Velocidad vs. Radio (galaxia)')
plt.show()
