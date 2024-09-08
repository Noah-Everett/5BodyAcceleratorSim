cmake_minimum_required(VERSION 3.10)
project(NBodySim)

# Add the include directory
include_directories(include)

# Find ROOT
find_package(ROOT REQUIRED COMPONENTS RIO Net)
include_directories(${ROOT_INCLUDE_DIRS})
link_directories(${ROOT_LIBRARY_DIR})

# Find Boost
find_package(Boost REQUIRED COMPONENTS filesystem system)
include_directories(${Boost_INCLUDE_DIRS})

# Add the executable
add_executable(NBodySim NBodySim.cpp)

# Link ROOT libraries
target_link_libraries(NBodySim ${ROOT_LIBRARIES})

# Link Boost libraries
target_link_libraries(NBodySim ${Boost_LIBRARIES})

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)