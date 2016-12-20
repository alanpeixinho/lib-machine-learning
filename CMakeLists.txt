#ML library CMAKE
#author Alan Peixinho (alan-peixinho@hotmail.com)
 
cmake_minimum_required(VERSION 3.1)

project(ML)

set(CMAKE_VERBOSE_MAKEFILE "ON")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

include_directories(include src .)

if(ML_GPU)
    add_definitions(-DML_GPU=1)
    find_package(CUDA REQUIRED)
    include(FindCUDA)
    include_directories(${CUDA_INCLUDE_DIRS})
endif()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu11 -ggdb -O3")

if(ML_DEBUG)
    add_definitions(-DML_DEBUG=1)
    set(CMAKE_CXX_FLAGS_DEBUG " ${CMAKE_CXX_FLAGS} -fsanitize=address")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} -fsanitize=address")
else()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
endif()

message(STATUS ${CUDA_CUBLAS_LIBRARIES})

find_package(Threads REQUIRED)

message(STATUS ${CMAKE_MODULE_PATH})

find_package( CBLAS REQUIRED )
find_package( LAPACK REQUIRED )
find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
endif()

option (USE_LAPACKE "Use LAPACKE C interface to LAPACK" ON)
option (USE_LAPACKE "Use BLAS C interface to BLAS" ON)
option (USE_OPENMP "Use OpenMP for multithreading" ON)
 
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
 
message(Compiler: "${CMAKE_C_COMPILER_ID}")
 
aux_source_directory(${ML_SOURCE_DIR}/src ML_SRC)
 
file(GLOB ML_INCLUDE
    ${ML_SOURCE_DIR}/include/*.h)

message(STATUS "ML library")
foreach( MLsourcefile ${ML_SRC} )
    message(STATUS "\t${MLsourcefile}")
endforeach(MLsourcefile ${ML_SRC})
 
#add_library(ml SHARED ${ML_SRC} ${ML_INCLUDE})
add_library(ml STATIC ${ML_SRC} ${ML_INCLUDE})

install(FILES ${ML_INCLUDE}
        DESTINATION include
        )


install (TARGETS ml
         ARCHIVE DESTINATION lib
         LIBRARY DESTINATION lib
         RUNTIME DESTINATION bin)
