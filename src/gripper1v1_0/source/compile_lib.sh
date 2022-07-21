#=============== BUILD SOME SHARED LIBRARIES ==============
# ---------------------------------------------------------

#========================================== CREATE VARIABLES
# ---------------------------------------------------------
. ./compile_env.sh



#========================================== BUILD GPODMODEL
# ---------------------------------------------------------
cd "$ROOT/build/gpodmodel"
mkdir -p build
cd ./build
cmake ..
make
make install
cd ..
rm -r build
cd $ROOT