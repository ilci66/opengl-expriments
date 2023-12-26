cmake_minimum_required(VERSION 3.10)
project(opengl-app)

set(CMAKE_CXX_STANDARD 17)

# Add include directories
include_directories(${CMAKE_SOURCE_DIR}/dependencies/include)

# Add library directories
link_directories(${CMAKE_SOURCE_DIR}/dependencies/library)

# Add source files
file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/*.cpp" "${CMAKE_SOURCE_DIR}/glad.c")

# Add executable
add_executable(app ${SOURCES})

# Add libraries
target_link_libraries(app
    ${CMAKE_SOURCE_DIR}/dependencies/library/libglfw.3.3.dylib
    "-framework OpenGL"
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreVideo"
    "-framework CoreFoundation"
)

# Set compiler options
target_compile_options(app PRIVATE
    -fdiagnostics-color=always
    -Wall
    -g
    -Wno-deprecated
)
