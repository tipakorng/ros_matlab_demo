# %Tag(FULLTEXT)%
cmake_minimum_required(VERSION 2.8.3)
project(matlab_demo)

# Configure CMake
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS roscpp roslib rospy std_msgs message_generation)
find_package(MATLAB REQUIRED)

## If Matlab is not found, raise error and quit
if(NOT MATLAB_FOUND)
    message(SEND_ERROR "MATLAB not found, nothing will be built.")
else(NOT MATLAB_FOUND)
    message(STATUS "MATLAB found, HOORAY!")
endif()

## Declare ROS messages and services
add_service_files(DIRECTORY srv FILES AddTwoInts.srv DotProduct.srv)

## Generate added messages and services
generate_messages(DEPENDENCIES std_msgs)

## Declare a catkin package
catkin_package()

# %EndTag(FULLTEXT)%
include_directories(${catkin_INCLUDE_DIRS} ${Matlab_INCLUDE_DIRS})

# Add executables
add_executable(add_two_ints_server src/add_two_ints_server.cpp)
target_link_libraries(add_two_ints_server ${catkin_LIBRARIES} ${MATLAB_LIBRARIES})
add_dependencies(add_two_ints_server matlab_demo_gencpp)

add_executable(add_two_ints_client src/add_two_ints_client.cpp)
target_link_libraries(add_two_ints_client ${catkin_LIBRARIES} ${MATLAB_LIBRARIES})
add_dependencies(add_two_ints_client matlab_demo_gencpp)

add_executable(dot_product_server src/dot_product_server.cpp)
target_link_libraries(dot_product_server ${catkin_LIBRARIES} ${MATLAB_LIBRARIES})
add_dependencies(dot_product_server matlab_demo_gencpp)

add_executable(dot_product_client src/dot_product_client.cpp)
target_link_libraries(dot_product_client ${catkin_LIBRARIES} ${MATLAB_LIBRARIES})
add_dependencies(dot_product_server matlab_demo_gencpp)
