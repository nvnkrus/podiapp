import os
import sys
import time
import numpy as np
from scipy import io, integrate, linalg, signal
from scipy.sparse.linalg import eigs

sys.path.insert(0,os.path.join(os.environ['DRSHARE'],'libpy'))
from libpy_system import *
from libpy_mathbox import *

fname = os.path.join('database','para','paraval.bin')
paraval = binread(fname=fname)
valIDs = [9, 11, 12, 14, 23, 25, 26, 28, 38, 39, 40, 41, 45, 46, 48, 51, 52, 53, 54, 55, 56, 58, 61, 63, 65, 66, 67, 68, 69, 70]
nparaval = len(valIDs)

## Read FE mesh of the soft gripper
fname1 = fullfile('database','mesh','gcrd.bin');
fname2 = fullfile('database','mesh','bfaces.bin');
gcrd = binread(fname1);		# FE nodal coordinates
bfaces = binread(fname2);	# FE mesh of boundary surface
nnode = gcrd.shape[0];		# total number of FE nodes
sdof = 3*nnode; 			# 

# available validating parameters
fname1 = fullfile('database','para','paraval.bin');
fname2 = fullfile('database','para','dispval.bin');
fname3 = fullfile('database','para','misesval.bin');
paraval = binread(fname1);
dispval = binread(fname2);
misesval = binread(fname3);

def validate_singlecase(valID,paraval,dispval,misesval):
	paras = paraval[valID,:]
	np.savetxt("parameter.csv", paras.reshape(1,3), delimiter=",",fmt='%.4f')
	flag = os.system(os.path.join(os.getcwd(),"run_main.sh"))

	print('==============================================\n')
	print('valID %d: h = %.2f, theta_x = %.2f, d_x = %.2f\n' 
		%(valID, paras[0], paras[1], paras[2]))

	## Abaqus solution
	disp_true = dispval[:,valID]
	mises_true = misesval[:,valID]

	## PODI-RBF solution
	fname1 = fullfile('result','drom.bin');
	fname2 = fullfile('result','mrom.bin');
	fname3 = fullfile('result','runTime.bin');
	disp_new = binread(fname1);
	mises_new = binread(fname2);
	runTime = binread(fname3)

	## evaluate the errors of displacement and stress
	# displacement
	err_rtne = rtne(disp_new,disp_true)*100
	err_rmse = rmse(disp_new,disp_true)

	print('Runtime %.4f ms' %(runTime))
	print('Speed %.4f Hz' %(1000/runTime))
	print('Displacement:\n')
	print('\tError L2: %.4f %%\n' %err_rtne)
	print('\tError rmse: %.4g \n' %err_rmse)
	print('\tMax value : Abaqus %.4g, PODI-RBF %.4g \n' %(np.max(np.abs(disp_true)),np.max(np.abs(disp_new))))

	# mises stress
	err_rtne = rtne(mises_new,mises_true)*100
	err_rmse = rmse(mises_new,mises_true)

	print('von Mises stress:\n')
	print('\tError L2: %.4f %%\n' %err_rtne)
	print('\tError rmse: %.4g \n' %err_rmse)
	print('\tMax value : Abaqus %.4g, PODI-RBF %.4g \n' 
		%(np.max(np.abs(mises_true)),np.max(np.abs(mises_new))))
	# if np.mod(valID,47) == 0:
	# 	time.sleep(30)

for inx in range(nparaval): # [0]: #
	valID = valIDs[inx]-1
	validate_singlecase(valID,paraval,dispval,misesval)
