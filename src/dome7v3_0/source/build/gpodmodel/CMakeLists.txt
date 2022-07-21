cmake_minimum_required(VERSION 3.1)
project(GPODMODEL)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 14) 
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}") # -O3 

# include all headers
set(LIB_SOURCE $ENV{SOURCE_GPODMODEL})
include_directories(${LIB_SOURCE} $ENV{SOURCE_OSLOADER} $ENV{SOURCE_MATRIXLOADER} $ENV{SOURCE_RBFMODEL} $ENV{EIGEN3} $ENV{RAPIDJSON})

# library source file
set(LIB_NAME GpodModel)
set(SOURCES ${LIB_SOURCE}/${LIB_NAME}.cpp)

# build library
add_library(${LIB_NAME} SHARED ${SOURCES})

# install library
install(TARGETS ${LIB_NAME} DESTINATION $ENV{PROGLIBS})
