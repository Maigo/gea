cmake_minimum_required(VERSION 2.8.9)
project(gea CXX)

# set(LICENSE_FILE "LICENSE.md")
set(README_FILE "README.md")

set(PROJECT_VERSION_MAJOR "0")
set(PROJECT_VERSION_MINOR "0")
set(PROJECT_VERSION_PATCH "0")
set(PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")

#################################################
# EXTENSIONS                                    #
#################################################
# add cmake extensions
include(${CMAKE_SOURCE_DIR}/cmake/extensions.cmake)

# add cmake module path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

## ######################################## ##
## PROJECT AND SOURCE STRUCTURE             ##

# Organize projects into folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

## ######################################## ##
## PROJECT DEPENDENCIES                     ##

# OpenGL
find_package(OPENGL REQUIRED)
find_package_check(OPENGL REQUIRED)

# Lua 5.1
#find_package(Lua51)

## ######################################## ##
## SUB-PROJECTS                             ##

# set up include-directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# external hash
add_subdirectory(external/hash)
# external random
add_subdirectory(external/random)
# external static (compile time) hash
#add_subdirectory(external/static_hash)

# gea math
add_subdirectory(libs/gea_math)
# gea binpack
#add_subdirectory(libs/gea_binpack)

# engine
add_subdirectory(engine)

## ######################################## ##
## BUILD                                    ##

# if (WIN32)
#   add_executable(${PROJECT_NAME} WIN32 main.cpp ${QT_RESOURCES} )
# endif (WIN32)