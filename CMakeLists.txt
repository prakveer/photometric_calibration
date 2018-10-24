cmake_minimum_required(VERSION 2.8.3)
project(online_photometric_calibration_version2)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)


set(CMAKE_BUILD_TYPE RelWithDebInfo)

# We need at least C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# set march=native unless specified
if(NOT CXX_MARCH)
  set(CXX_MARCH native)
endif()
SET(CMAKE_CXX_FLAGS_RELEASE "-march=${CXX_MARCH} ${CMAKE_CXX_FLAGS_RELEASE}")
SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO  "-march=${CXX_MARCH} ${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")

# warnings
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-sign-compare")



## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  cv_bridge
  image_transport
  roscpp
  sensor_msgs
)

## System dependencies are found with CMake's conventions
 #find_package(Boost REQUIRED COMPONENTS system)
find_package(OpenCV REQUIRED)
find_package(Threads REQUIRED)




###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if your package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
#  INCLUDE_DIRS include
 # LIBRARIES image_transport_tutorial
#  CATKIN_DEPENDS cv_bridge image_transport roscpp sensor_msgs
 # DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories( include  ${catkin_INCLUDE_DIRS} )
include_directories(SYSTEM ${OpenCV_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/src)


set(ONLINE_CALIB_SOURCE_FILES
  src/Database.cpp
  src/GainRobustTracker.cpp
  src/ImageReader.cpp
  src/JacobianGenerator.cpp
  src/NonlinearOptimizer.cpp
  src/OptimizationBlock.cpp
  src/RapidExposureTimeEstimator.cpp
  src/Tracker.cpp
  src/VignetteModel.cpp
)


file(GLOB_RECURSE _INCLUDE_FILES "src/*.h" "src/*.hpp")
add_custom_target(_include_files_fix_target SOURCES ${_INCLUDE_FILES})

#libraries
add_library(online_pcalib SHARED ${ONLINE_CALIB_SOURCE_FILES})
target_link_libraries(online_pcalib )

#executables
add_executable(image_pub src/image_publisher.cpp)
target_link_libraries(image_pub ${OpenCV_LIBRARIES} ${catkin_LIBRARIES} )

add_executable(image_sub src/image_subscriber.cpp)
target_link_libraries(image_sub ${OpenCV_LIBRARIES} ${catkin_LIBRARIES} )


#add_executable(online_pcalib_demo src/main.cpp)
#target_link_libraries(online_pcalib_demo  online_pcalib ${OpenCV_LIBRARIES}   ${catkin_LIBRARIES}  ${CMAKE_THREAD_LIBS_INIT} )



#add_executable(test1 src/test1.cpp)
#target_link_libraries(test1 online_pcalib ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})

add_executable(test2 src/test2.cpp)
target_link_libraries(test2 online_pcalib ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})
