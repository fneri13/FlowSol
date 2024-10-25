import numpy as np
import matplotlib.pyplot as plt

data = np.loadtxt("Sol.dat", skiprows=1)

fig, ax = plt.subplots(2, 2, figsize=(12, 8))
ax[0, 0].plot(data[:,0], data[:,1])
ax[0, 0].set_ylabel('Density')

ax[0, 1].plot(data[:,0], data[:,2])
ax[0, 1].set_ylabel('Velocity')

ax[1, 0].plot(data[:,0], data[:,3])
ax[1, 0].set_ylabel('Pressure')

ax[1, 1].plot(data[:,0], data[:,4])
ax[1, 1].set_ylabel('Energy')

for row in ax:
    for col in row:
        col.set_xlabel('x')
        col.grid(alpha=0.3)

plt.show()