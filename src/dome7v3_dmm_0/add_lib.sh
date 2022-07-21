ROOT=$(pwd)
ROOT=$(echo $ROOT | tr -d '\r')
LD_LIBRARY_PATH=$ROOT/dynalib
export LD_LIBRARY_PATH