#============== CREATE SOME SYSTEM VARIABLES ==============
# ---------------------------------------------------------

#========================================== BUILD ESSENTIAL
# ---------------------------------------------------------
## Install essential packages
## install build essential, cmake and git
# sudo apt-get install build-essential 
# sudo apt-get update
# sudo apt-get -y install cmake
## download git package (if not available)
# sudo apt-get install git 
# sudo apt-get update

#=========================================== SHARED LIBRARY
# ---------------------------------------------------------
ROOT=$(pwd)
ROOT=$(echo $ROOT | tr -d '\r')
## Path to the shared library
export SOURCE_ROOT=$DRPRJ/clang/cpp/libpodi/v02
# export PROGLIBS=$SOURCE_ROOT/dynalib
export PROGLIBS=$DRSHARE/package/gripper1v1_0/dynalib
# export GPODLIBS=$DRPRJ/rom/snu/gripper/podi_v1/validating/rootpath/dynalib
#=========================================== EIGEN TEMPLATE
# ---------------------------------------------------------
## Path to the Eigen3 package
# If Eigen3 is not available in your computer
# download eigen package 
# git clone https://gitlab.com/libeigen/eigen.git
# export EIGEN3=$ROOT/eigen

# If you have eigen installed, please modify the above variable 
# using the corresponding path in your computer
# For example, in my computer
export EIGEN3=$MYSOFTWARE/cpp/eigen-3.4-rc1

#======================================= RAPIDJSON TEMPLATE
# ---------------------------------------------------------
export RAPIDJSON=$MYSOFTWARE/cpp/rapidjson/include

#========================================== MY PODI LIBRARY
# ---------------------------------------------------------
export SOURCE_OSLOADER=$SOURCE_ROOT/source/osloader
export SOURCE_MATRIXLOADER=$SOURCE_ROOT/source/matrixloader
export SOURCE_RBFMODEL=$SOURCE_ROOT/source/rbfmodel
export SOURCE_GPODMODEL=$ROOT/gpodmodel

# export SOURCE_CONFIGURE=$SOURCE_ROOT/source/configure
# export SOURCE_PODIMODEL=$SOURCE_ROOT/source/podimodel
# export SOURCE_NAIVEMODEL=$SOURCE_ROOT/source/naivemodel
# export SOURCE_INTERPMODEL=$SOURCE_ROOT/source/interpmodel
