cmake_minimum_required(VERSION 3.10)
project(NBodySim)

# Add the include directory
include_directories(include)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
message(STATUS "Using C++${CMAKE_CXX_STANDARD}")

# Find ROOT
find_package(ROOT REQUIRED COMPONENTS RIO Net)
message(STATUS "Found ROOT version: ${ROOT_VERSION}")
include_directories(${ROOT_INCLUDE_DIRS})
message(STATUS "Using ROOT include directory: ${ROOT_INCLUDE_DIRS}")
link_directories(${ROOT_LIBRARY_DIR})

# Find Boost
find_package(Boost REQUIRED COMPONENTS filesystem system)
message(STATUS "Found Boost version: ${Boost_VERSION}")
include_directories(${Boost_INCLUDE_DIRS})
message(STATUS "Using Boost include directory: ${Boost_INCLUDE_DIRS}")

# Find CLHEP
find_package(CLHEP REQUIRED)
message(STATUS "Found CLHEP version: ${CLHEP_VERSION}")
include_directories(${CLHEP_INCLUDE_DIRS})
message(STATUS "Using CLHEP include directory: ${CLHEP_INCLUDE_DIRS}")

# Find Yaml-cpp
find_package(yaml-cpp REQUIRED)
message(STATUS "Found yaml-cpp version: ${YAML_CPP_VERSION}")
include_directories(${YAML_CPP_INCLUDE_DIR})
message(STATUS "Using yaml-cpp include directory: ${YAML_CPP_INCLUDE_DIR}")

# Add the executable
add_executable(NBodySim NBodySim.cpp)

# Link ROOT libraries
target_link_libraries(NBodySim ${ROOT_LIBRARIES})

# Link Boost libraries
target_link_libraries(NBodySim ${Boost_LIBRARIES})