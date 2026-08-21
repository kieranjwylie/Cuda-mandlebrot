from plotting.plotclass import BasePlot
import numpy as np

fig = BasePlot()
data_CUDA = np.loadtxt("../cuda_log.txt", unpack = True)
data_MPI = np.loadtxt("../MPI_log.txt", unpack = True)

#data_CUDA[0] = data_CUDA[0]**2
#data_MPI[0] = data_MPI[0]**2

fig.add_dataset(data_CUDA[0], data_CUDA[1], label = "CUDA")
fig.add_dataset(data_CUDA[0], data_MPI[1], label = "MPI")

fig.xlabel("Number of vertices")
fig.ylabel("Time taken (s)")
#fig.logscale_x()
fig.draw()
fig.legend()
fig.show()