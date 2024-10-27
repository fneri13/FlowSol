import numpy as np
import matplotlib.pyplot as plt
import os

# Specify the folder
folder_path = "Results"

# Check if the folder exists
if os.path.isdir(folder_path):
    # List all files in the folder
    files = [f for f in os.listdir(folder_path) if os.path.isfile(os.path.join(folder_path, f))]
    files = sorted(files)
    print("Files in 'Results' folder:")
    for file in files:
        print(file)
else:
    print(f"The folder '{folder_path}' does not exist.")

timesteps = len(files)
dum = 1
fig, ax = plt.subplots(2, 2, figsize=(12, 8))
for file in files:
    data = np.loadtxt(folder_path+ '/'+file, skiprows=1)

    for row in ax:
        for col in row:
            col.cla()
            col.set_xlabel('x')
            col.grid(alpha=0.3)
    
    ax[0, 0].plot(data[:,0], data[:,1])
    ax[0, 0].set_ylabel('Density')

    ax[0, 1].plot(data[:,0], data[:,2])
    ax[0, 1].set_ylabel('Velocity')

    ax[1, 0].plot(data[:,0], data[:,3])
    ax[1, 0].set_ylabel('Pressure')

    ax[1, 1].plot(data[:,0], data[:,4])
    ax[1, 1].set_ylabel('Energy')

    plt.suptitle('Time Step %i:%i' %(dum, timesteps))
    plt.pause(0.001)
    dum += 1

plt.show()