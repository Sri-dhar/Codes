# CMakeLists.txt

cmake_minimum_required(VERSION 3.10)

project(GraphExample)

# Add your source file
add_executable(graph graph.cpp)

# Optional: Set C++ standard (adjust as needed)
set_target_properties(graph PROPERTIES CXX_STANDARD 11)

# Optional: Enable compiler optimizations (adjust as needed)
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(graph PRIVATE -O2)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    target_compile_options(graph PRIVATE /O2)
endif()

# Set the output directory for the executable
set_target_properties(graph PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# Custom target to run the executable
add_custom_target(run
    COMMAND "${CMAKE_BINARY_DIR}/bin/graph"
    DEPENDS graph
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Optional: Add the 'run' target as the default target
add_custom_target(default
    DEPENDS run
)
