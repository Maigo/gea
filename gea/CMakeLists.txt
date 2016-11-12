cmake_minimum_required(VERSION 3.5.0)
project(gea VERSION 0.0.0 LANGUAGES CXX)

# set(LICENSE_FILE "LICENSE.md")
set(README_FILE "README.md")

#################################################
# EXTENSIONS                                    #
#################################################
# add cmake extensions
include(${CMAKE_SOURCE_DIR}/cmake/extensions.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/extensions_gea.cmake)

# add cmake module path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

## ######################################## ##
## PROJECT AND SOURCE STRUCTURE             ##

# Organize projects into folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

## ######################################## ##
## PROJECT DEPENDENCIES                     ##

# OpenGL
find_package(OPENGL MODULE REQUIRED)
find_package_check(OPENGL REQUIRED)

# Lua 5.1
#find_package(Lua51)

## ######################################## ##
## SUB-PROJECTS                             ##

# set up include-directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# external libraries
#add_subdirectory(external/box2d)
add_subdirectory(external/sdl)
add_subdirectory(external/freetype)
add_subdirectory(external/glfw)

add_subdirectory(external/murmur)
add_subdirectory(external/sfmt)

add_subdirectory(external/gtest)

# gea libraries
add_subdirectory(libs/gea_core)
add_subdirectory(libs/gea_data)
add_subdirectory(libs/gea_eastl)
add_subdirectory(libs/gea_hash)
add_subdirectory(libs/gea_math)
add_subdirectory(libs/gea_math_cg)
add_subdirectory(libs/gea_random)

# gea demo libraries
add_subdirectory(libs/gea_demo_core)
add_subdirectory(libs/gea_demo_sdl)

# gea engine
add_subdirectory(engine)


## ######################################## ##
## BUILD                                    ##

# test
add_subdirectory(test/sdl_bin_pack)
add_subdirectory(test/sdl_convex_hull)
add_subdirectory(test/sdl_point_reduce)
