cmake_minimum_required(VERSION 3.1)
project(DOME7DEC09)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 11) 
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3") 

# shared library:
set(PROJECT_LINK_LIBS libGpodModel.so libRbfModel.so libMatrixLoader.so libOSLoader.so)
link_directories($ENV{PROGLIBS})

# include all headers
include_directories($ENV{EIGEN3} $ENV{RAPIDJSON} $ENV{SOURCE_OSLOADER} $ENV{SOURCE_MATRIXLOADER} $ENV{SOURCE_RBFMODEL} $ENV{SOURCE_GPODMODEL})

# Can manually add the sources using the set command as follows:
set(SOURCES ../../../source.cpp)

add_executable(main ${SOURCES})
target_link_libraries(main ${PROJECT_LINK_LIBS})


# if(DEFINED ENV{EIGEN3})
# 	message($ENV{$})
# endif()

# message($ENV{EIGEN3})
# message($ENV{RAPIDJSON})
# message($ENV{SOURCE_OSLOADER})
# message($ENV{SOURCE_MATRIXLOADER}) 
# message($ENV{SOURCE_CONFIGURE}) 
# message($ENV{SOURCE_RBFMODEL})
# message($ENV{SOURCE_PODIMODEL})

# cmake_minimum_required(VERSION 3.1)
# project(MatrixVal)
# set(CMAKE_BUILD_TYPE Release)
# set(CMAKE_CXX_STANDARD 11) 
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -DMKL_ILP64 -DEIGEN_USE_MKL_ALL -DEIGEN_VECTORIZE_SSE4_2 -m64 -fopenmp")
# # MKL 
# set(MKL_INCLUDE_DIR /data1/software/intel/mkl/include)
# set(MKL_LIB_DIR /data1/software/intel/mkl/lib/intel64)
# set(MKL_LIBRARY_FLAGS "-Wl,--no-as-needed -lmkl_intel_lp64 -lmkl_intel_thread -lmkl_core -liomp5 -lpthread -lm -ldl")
# # Eigen 
# set(EIGEN3_INCLUDE_DIR /data1/software/cpp/eigen)
# set(RAPIDJSON_INCLUDE_DIR /data1/software/cpp/rapidjson/include)
# set(OS_INCLUDE_DIR /data1/nhan/Dropbox/Dropbox/project/clang/cpp/LIBCPP/OS)
# set(MATH_INCLUDE_DIR /data1/nhan/Dropbox/Dropbox/project/clang/cpp/LIBCPP/Math)
# set(PODI_INCLUDE_DIR /data1/nhan/Dropbox/Dropbox/project/clang/cpp/LIBCPP/ROM/PODI)
# set(DYNALIB_DESTINATION /data1/nhan/Dropbox/Dropbox/project/clang/cpp/LIBCPP/DynaLib)

# # For the shared library:
# set (PROJECT_LINK_LIBS libPodiModel.so libRbfModel.so libConfigure.so libMatrixLoader.so libOSLoader.so)
# link_directories(${DYNALIB_DESTINATION} ${MKL_LIB_DIR})

# # Bring the headers, such as Student.h into the project
# include_directories(${MKL_INCLUDE_DIR} ${EIGEN3_INCLUDE_DIR} ${RAPIDJSON_INCLUDE_DIR} ${OS_INCLUDE_DIR} ${MATH_INCLUDE_DIR} ${PODI_INCLUDE_DIR})

# # Can manually add the sources using the set command as follows:
# set(SOURCES PodiVal.cpp)

# add_executable(PodiVal ${SOURCES})
# target_link_libraries(PodiVal ${PROJECT_LINK_LIBS} ${MKL_LIBRARY_FLAGS})
