#################################################
# DEMO: GLFW SIMPLE                             #
#################################################
cmake_minimum_required(VERSION 3.5.0)

set(DEMO glfw_simple)

message(STATUS "Building ${DEMO}")

#project (${DEMO} VERSION 0.0.0)

# list dependencies
set(DEP_${DEMO}
    ext_glad
    ext_glfw
)

if (WIN32)
    list(APPEND DEP_${DEMO}
        winmm.lib
        version.lib
        imm32.lib
    )
endif (WIN32)

# source build variables
set(INC_${DEMO}) # include
set(INL_${DEMO}) # inline
set(SRC_${DEMO}) # source

# core
list(APPEND INC_${DEMO}
)
list(APPEND INL_${DEMO}
)
list(APPEND SRC_${DEMO}
    src/main.cpp
)

# force include of global header
force_include_header(global.h)

# organize source folders
source_group_ext(PREFIX "include" UNPREFIX "src" FILES ${INC_${DEMO}})
source_group_ext(PREFIX "source"  UNPREFIX "src" FILES ${SRC_${DEMO}} ${INL_${DEMO}})

# add target
add_executable(${DEMO} ${SRC_${DEMO}})
include_directories(${PROJECT_SOURCE_DIR} src)

# add dependencies
target_link_libraries(${DEMO} ${DEP_${DEMO}})

# organize test into solution folder
project_group(${DEMO} "demos")

# clean-up
unset(INC_${DEMO})
unset(INL_${DEMO})
unset(SRC_${DEMO})
