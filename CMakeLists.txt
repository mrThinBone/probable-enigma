# READ https://www.studyplan.dev/sdl3/sdl3-cmake

# Set the minimum version of CMake required
cmake_minimum_required(VERSION 3.23)

# Define the project
project(
  SDLTryOut
  VERSION 1.0
  DESCRIPTION "SDL3 Try out"
  LANGUAGES CXX
)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ${CMAKE_BINARY_DIR} refers to the directory where we generate our build, which we've configured in our presets to be the /build directory.
# $<CONFIGURATION> is a special "generator expression" that CMake replaces with the current build type (e.g., Debug, Release).
set(
  CMAKE_RUNTIME_OUTPUT_DIRECTORY
  "${CMAKE_BINARY_DIR}/$<CONFIGURATION>"
)

set(
  CMAKE_LIBRARY_OUTPUT_DIRECTORY
  "${CMAKE_BINARY_DIR}/$<CONFIGURATION>"
)

add_executable(SDLTryOut
  src/main.cpp
)

if(APPLE)
  set_target_properties(SDLTryOut PROPERTIES
    INSTALL_RPATH "@executable_path;@loader_path"
    BUILD_WITH_INSTALL_RPATH TRUE
    MACOSX_RPATH TRUE
  )
elseif(UNIX)
  set_target_properties(SDLTryOut PROPERTIES
    INSTALL_RPATH "$ORIGIN"
    BUILD_WITH_INSTALL_RPATH TRUE
  )
endif()

# Specify that we want to build SDL_TTF's dependencies
set(SDLTTF_VENDORED ON) 

# Set a variable for our vendor directory
set(VENDOR_DIR "${PROJECT_SOURCE_DIR}/vendor")

# Add the SDL libraries from our submodules
add_subdirectory(${VENDOR_DIR}/SDL) 
add_subdirectory(${VENDOR_DIR}/SDL_image) 
add_subdirectory(${VENDOR_DIR}/SDL_ttf)

target_link_libraries(SDLTryOut 
  SDL3::SDL3 
  SDL3_image::SDL3_image 
  SDL3_ttf::SDL3_ttf 
)