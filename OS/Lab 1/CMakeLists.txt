cmake_minimum_required(VERSION 3.10)
project(lab1)

# Add all .c files in the current directory to the executable
file(GLOB SOURCES "*.c")
foreach(sourcefile ${SOURCES})
    get_filename_component(filename ${sourcefile} NAME_WE)
    add_executable(${filename} ${sourcefile})
endforeach(sourcefile ${SOURCES})