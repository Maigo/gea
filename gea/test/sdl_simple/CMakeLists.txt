#################################################
# TEST: SDL SIMPLE                              #
#################################################
cmake_minimum_required(VERSION 3.5.0)

set(TEST sdl_simple)

message(STATUS "Building ${TEST}")

#project (${TEST} VERSION 0.0.0)

# List dependencies
set(DEP_${TEST}
	gea_math
	gea_math_graph
	ext_sdl
)

message(STATUS "[WARNING] Building using win32 libraries!")
set(DEP_WIN_${TEST}
	winmm.lib
	version.lib
	imm32.lib
)

# source build variables
set(INC_${TEST})
set(INL_${TEST})
set(SRC_${TEST})

list(APPEND SRC_${TEST}
  src/main.cpp
)

# Force include of global header
force_include_header(global.h)

# Organize source folders
source_group("include" FILES ${INC_${TEST}})
source_group("source" FILES ${SRC_${TEST}} ${INL_${TEST}})

# Add the executable
add_executable(${TEST} ${SRC_${TEST}})
include_directories(${PROJECT_SOURCE_DIR} src ${ext_sdl_INCLUDE_DIR})

# Add dependencies
target_link_libraries(${TEST} ${DEP_${TEST}} ${DEP_WIN_${TEST}})

# Organize test into solution folder
project_group(${TEST} "tests")

# Clean-up
unset(INC_${TEST})
unset(INL_${TEST})
unset(SRC_${TEST})
unset(TEST)
