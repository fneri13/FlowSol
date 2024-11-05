import numpy as np
import matplotlib.pyplot as plt

data = np.loadtxt("mandelbrot.dat")
data /= np.max(data)
isize, jsize = data.shape[0], data.shape[1]

# for i in range(isize):
#     for j in range(jsize):
#         if data[i,j] >=0.9:
#             data[i,j] = 1
#         elif data[i,j] <= 0.1:
#             pass
#         else:
#             data[i,j] = 0.5

x = np.linspace(-2.6, 1, isize)
y = np.linspace(-1.2, 1.2, jsize)
xgrid, ygrid = np.meshgrid(x, y, indexing='ij')

plt.figure()
plt.contourf(xgrid, ygrid, data, levels=8)
plt.show()