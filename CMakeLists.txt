cmake_minimum_required(VERSION 3.15)
project(gradebook)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add executable with main source file only
add_executable(gradebook 
    gradebook/main.cpp
)

# Include directories for tabulate library
target_include_directories(gradebook PRIVATE 
    ${CMAKE_SOURCE_DIR}/gradebook
    ${CMAKE_SOURCE_DIR}/gradebook/tabulate
)

# Set output directory to build/Debug
set_target_properties(gradebook PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/build/Debug
)

# Set locale environment
set(ENV{LC_ALL} "C")
