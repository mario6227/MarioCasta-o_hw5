import numpy as np
import matplotlib.pyplot as plt

file = np.genfromtxt('RadialVelocities.dat', skip_header = 1)
r = file[:,0]
v = file[:,1]

bb = 0.2497
bd = 5.16
ad = 0.3105
ah = 64.3

file = np.genfromtxt('parametros.txt', delimiter = ' ')
Mb = file[0]
Md = file[1]
Mh = file[2]

vel = np.zeros(300)
pb = np.sqrt(Mb) * r / (r**2 + bb**2)**(3.0/4.0)
pd = np.sqrt(Md) * r / (r**2 + (bd + ad)**2)**(3.0/4.0)
ph = np.sqrt(Mh) / (r**2 + ah**2)**(1.0/4.0)

vel = pb + pd + ph

plt.scatter(r,v, s = 10, c = 'green', alpha = 0.3, label = 'observaciones')
plt.plot(r, vel, c = 'red', label = 'modelo')
plt.xlabel('Radio (kpc)')
plt.ylabel('Velocidad (km/s)')
plt.title('Velocidad vs. Radio (galaxia)')
plt.legend(loc = 0)
plt.savefig('Velocidades.pdf')
