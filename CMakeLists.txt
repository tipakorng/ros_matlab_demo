# %Tag(FULLTEXT)%
cmake_minimum_required(VERSION 2.8.3)
#cmake_minimum_required(VERSION 3.3)
project(matlab_example)

# Configure CMake
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/matlab_example/cmake)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs message_generation)
#set(Matlab_ROOT_DIR "/usr/local/MATLAB/R2015a")
#find_package(Matlab REQUIRED)
find_package(MATLAB REQUIRED)

## If Matlab is not found, raise error and quit
if(NOT MATLAB_FOUND)
    message(SEND_ERROR "MATLAB not found, nothing will be built.")
else(NOT MATLAB_FOUND)
    message(STATUS "MATLAB found, HOORAY!")
endif()

## Declare ROS messages and services
add_service_files(DIRECTORY srv FILES AddTwoInts.srv)

## Generate added messages and services
generate_messages(DEPENDENCIES std_msgs)

## Declare a catkin package
catkin_package()

# %EndTag(FULLTEXT)%
#include_directories(${catkin_INCLUDE_DIRS} ${MATLAB_INCLUDE_DIR})
include_directories(${catkin_INCLUDE_DIRS} ${Matlab_INCLUDE_DIRS})

add_executable(add_two_ints_server src/add_two_ints_server.cpp)
target_link_libraries(add_two_ints_server ${catkin_LIBRARIES} ${MATLAB_LIBRARIES})
#target_link_libraries(add_two_ints_server ${catkin_LIBRARIES} ${Matlab_ENG_LIBRARY} ${Matlab_MX_LIBRARY})
add_dependencies(add_two_ints_server matlab_example_gencpp)

add_executable(add_two_ints_client src/add_two_ints_client.cpp)
target_link_libraries(add_two_ints_client ${catkin_LIBRARIES} ${MATLAB_LIBRARIES})
#target_link_libraries(add_two_ints_client ${catkin_LIBRARIES} ${Matlab_ENG_LIBRARY} ${Matlab_MX_LIBRARY})
add_dependencies(add_two_ints_client matlab_example_gencpp)
