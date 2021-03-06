#################################################
# DEMO: GLFW SANDBOX                            #
#################################################
cmake_minimum_required(VERSION 3.5.0)

set(DEMO glfw_sandbox)

message(STATUS "Building ${DEMO}")

#project (${DEMO} VERSION 0.0.0)

# list dependencies
set(DEP_${DEMO}
    gea_math
    gea_math_cg
    gea_demo_glfw
)

set(DEP_EXT_${DEMO})
if (WIN32)
    list(APPEND DEP_EXT_${DEMO}
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
    src/gea/demo/glfw_sandbox/application.h
)
list(APPEND INL_${DEMO}
)
list(APPEND SRC_${DEMO}
    src/gea/demo/glfw_sandbox/application.cpp
    src/main.cpp
)

# force include of global header
force_include_header(global.h)

# organize source folders
source_group_ext(PREFIX "include" UNPREFIX "src" FILES ${INC_${DEMO}})
source_group_ext(PREFIX "source"  UNPREFIX "src" FILES ${SRC_${DEMO}} ${INL_${DEMO}})

# add target
add_executable(${DEMO} ${SRC_${DEMO}} ${INL_${DEMO}} ${INC_${DEMO}})
include_directories(${PROJECT_SOURCE_DIR} src ${ext_sdl_INCLUDE_DIR})

# add dependencies
target_link_libraries(${DEMO} ${DEP_${DEMO}} ${DEP_EXT_${DEMO}} )
copy_imported_targets(${DEMO} ${DEP_${DEMO}})

# add runtime arguments
set_command_arguments(${DEMO} "test -a arg0 arg1 -b -c")

# organize test into solution folder
project_group(${DEMO} "demos")

# clean-up
unset(INC_${DEMO})
unset(INL_${DEMO})
unset(SRC_${DEMO})
