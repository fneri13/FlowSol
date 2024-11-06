import numpy as np
import matplotlib.pyplot as plt
from Grid.src.functions import eriksson_stretching_function_initial

"""
INPUT PARAMETERS
"""
NR = 5
NTHETA = 12
R_CYL = 1
R_OUT = 40*R_CYL


"""
GENERATE THE 2D GRID
"""
r = R_CYL+(R_OUT-R_CYL)*eriksson_stretching_function_initial(np.linspace(0, 1, NR), alpha=4)
theta = np.linspace(0, 2*np.pi, NTHETA)

rgrid, theta_grid = np.meshgrid(r, theta, indexing='ij')
xgrid = rgrid*np.cos(theta_grid)
ygrid = rgrid*np.sin(theta_grid)

plt.figure()
for i in range(NR):
    plt.plot(xgrid[i,:], ygrid[i,:], 'C0')
for j in range(NTHETA):
    plt.plot(xgrid[:,j], ygrid[:,j], 'C1')
# plt.show()

"""
WRITE MESH FILE
"""
mesh_name = "2D_Cylinder_%i_%i.msh" %(NR, NTHETA)
with open(mesh_name, 'w') as file:
    file.write("NDIM= 2\n")
    file.write("I_NODES= %i\n" %NR)
    file.write("J_NODES= %i\n" %NTHETA)
    file.write("INDEXING= IJ\n")
    for i in range(NR):
        for j in range(NTHETA):
            file.write("%.12e %.12e\n" %(xgrid[i,j], ygrid[i,j]))


