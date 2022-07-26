#=============== BUILD SOME SHARED LIBRARIES ==============
# ---------------------------------------------------------

#========================================== CREATE VARIABLES
# ---------------------------------------------------------
. ./compile_env.sh

#======================================= BUILD MAIN PROGRAM
# ---------------------------------------------------------
cd "$ROOT/build/main"
mkdir -p build
cd ./build
cmake ..
make
cp main ../../../..
cd ..
rm -r build
cd $ROOT