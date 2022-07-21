import os
import sys

import numpy as np
from scipy import io, integrate, linalg, signal
from scipy.sparse.linalg import eigs

paraval = np.array([[55, 15, 2.5],
					[55, 15, 7.5],
					[55, 15, 10],
					[55, 15, 15],
					[95, 15, 2.5],
					[95, 15, 7.5],
					[95, 15, 10],
					[95, 15, 15],
					[65, 15, 5],
					[65, 15, 7.5],
					[65, 15, 10],
					[65, 15, 12.5],
					[62.5, 0, 5],
					[62.5, 0, 7.5],
					[62.5, 0, 12.5],
					[62.5, 15, 2.5],
					[62.5, 15, 5],
					[62.5, 15, 7.5],
					[62.5, 15, 10],
					[62.5, 15, 12.5],
					[62.5, 15, 15],
					[77.5, 0, 2.5],
					[77.5, 0, 10],
					[77.5, 0, 15],
					[77.5, 15, 2.5],
					[77.5, 15, 5],
					[77.5, 15, 7.5],
					[77.5, 15, 10],
					[77.5, 15, 12.5],
					[77.5, 15, 15]])

nparaval = nparaval = paraval.shape[0][0]
for id in range(nparaval):
	np.savetxt("parameter.csv", paraval[id,:], delimiter=",")
	os.system(os.path.join(os.getcwd(),"main"))