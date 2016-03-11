# %Tag(FULLTEXT)%
cmake_minimum_required(VERSION 2.8.3)
#cmake_minimum_required(VERSION 3.3)
project(matlab_example)

# Configure CMake
#set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/src/matlab_example/cmake_modules)

# Set matlab path
SET(MATLAB_FOUND 0)
IF( "$ENV{MATLAB_ROOT}" STREQUAL "" )
    MESSAGE(STATUS " " )
    MESSAGE(STATUS " " )
    MESSAGE(STATUS " " )
    MESSAGE(STATUS " MATLAB_ROOT environment variable not set." )
    MESSAGE(STATUS " In Linux append the following to your .bashrc file:" )
    MESSAGE(STATUS " >>> export MATLAB_ROOT=/usr/local/MATLAB/R2014a <<<" )
    MESSAGE(STATUS " be sure to pick the correct version of Matlab" )
    MESSAGE(STATUS " " )
    MESSAGE(STATUS " " )
    MESSAGE(STATUS " " )
    MESSAGE(FATAL_ERROR " No matlab found. Follow the instructions above." )
ELSE("$ENV{MATLAB_ROOT}" STREQUAL "" )

    FIND_PATH(MATLAB_INCLUDE_DIR mex.h
            $ENV{MATLAB_ROOT}/extern/include)

    INCLUDE_DIRECTORIES(${MATLAB_INCLUDE_DIR})

    FIND_LIBRARY( MATLAB_MEX_LIBRARY
            NAMES libmex mex
            PATHS $ENV{MATLAB_ROOT}/bin $ENV{MATLAB_ROOT}/extern/lib
            PATH_SUFFIXES glnxa64 glnx86)

    FIND_LIBRARY( MATLAB_ENG_LIBRARY
            NAMES libeng eng
            PATHS $ENV{MATLAB_ROOT}/bin $ENV{MATLAB_ROOT}/extern/lib
            PATH_SUFFIXES glnxa64 glnx86)

    FIND_LIBRARY( MATLAB_MX_LIBRARY
            NAMES libmx mx
            PATHS $ENV{MATLAB_ROOT}/bin $ENV{MATLAB_ROOT}/extern/lib
            PATH_SUFFIXES glnxa64 glnx86)

    MESSAGE (STATUS "MATLAB_ROOT: $ENV{MATLAB_ROOT}")

ENDIF("$ENV{MATLAB_ROOT}" STREQUAL "" )

# This is common to UNIX and Win32:
SET(MATLAB_LIBRARIES
        ${MATLAB_MEX_LIBRARY}
        ${MATLAB_MX_LIBRARY}
        ${MATLAB_ENG_LIBRARY}
        )

IF(MATLAB_INCLUDE_DIR AND MATLAB_LIBRARIES)
    SET(MATLAB_FOUND 1)
    MESSAGE(STATUS "Matlab libraries will be used")
ENDIF(MATLAB_INCLUDE_DIR AND MATLAB_LIBRARIES)

MARK_AS_ADVANCED(
        MATLAB_LIBRARIES
        MATLAB_ENG_LIBRARY
        MATLAB_MEX_LIBRARY
        MATLAB_MX_LIBRARY
        MATLAB_INCLUDE_DIR
        MATLAB_FOUND
        MATLAB_ROOT
)

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs message_generation)
#find_package(Matlab 8.5 REQUIRED)
#find_package(Matlab REQUIRED)

## Declare ROS messages and services
add_service_files(DIRECTORY srv FILES AddTwoInts.srv)

## Generate added messages and services
generate_messages(DEPENDENCIES std_msgs)

## Declare a catkin package
catkin_package()

# %EndTag(FULLTEXT)%
include_directories(${catkin_INCLUDE_DIRS} ${MATLAB_INCLUDE_DIR})
#include_directories(${catkin_INCLUDE_DIRS} ${Matlab_INCLUDE_DIRS})

add_executable(add_two_ints_server src/add_two_ints_server.cpp)
target_link_libraries(add_two_ints_server ${catkin_LIBRARIES} ${MATLAB_LIBRARIES})
#target_link_libraries(add_two_ints_server ${catkin_LIBRARIES} ${Matlab_ENG_LIBRARY})
add_dependencies(add_two_ints_server matlab_example_gencpp)

add_executable(add_two_ints_client src/add_two_ints_client.cpp)
target_link_libraries(add_two_ints_client ${catkin_LIBRARIES} ${MATLAB_LIBRARIES})
#target_link_libraries(add_two_ints_client ${catkin_LIBRARIES} ${Matlab_ENG_LIBRARY})
add_dependencies(add_two_ints_client matlab_example_gencpp)
