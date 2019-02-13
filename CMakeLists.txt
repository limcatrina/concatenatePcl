cmake_minimum_required(VERSION 2.8.3)
project(concat_pcl)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED
  roscpp
  sensor_msgs
  pcl_conversions
  pcl_ros
)

find_package(PCL REQUIRED)

catkin_package(
  CATKIN_DEPENDS
    roscpp
    sensor_msgs
    pcl_conversions
    pcl_ros
)

find_package(Boost REQUIRED COMPONENTS system)

include_directories(
  include
    ${catkin_INCLUDE_DIRS}
    ${PCL_INCLUDE_DIRS})

link_directories(${PCL_LIBRARY_DIRS})

add_definitions(${PCL_DEFINITIONS})

add_executable(concat_pcl src/concat_pcl.cpp)
target_link_libraries(concat_pcl ${catkin_LIBRARIES} ${PCL_LIBRARIES})
