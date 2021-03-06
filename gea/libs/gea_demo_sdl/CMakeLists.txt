#################################################
# LIB: GEA DEMO SDL                             #
#################################################

set(LIB gea_demo_sdl)

message(STATUS "Building ${LIB}")

# list dependencies
set(DEP_${LIB}
    gea_core
    gea_math
    gea_demo_core
    ext_sdl
)

# source build variables
set(INC_${LIB} ) # include
set(INL_${LIB} ) # inline
set(SRC_${LIB} ) # source

# core
list(APPEND INC_${LIB}
    src/gea/demo/sdl/event/sdl_system_event_pump.h
    src/gea/demo/sdl/render/sdl_immediate_renderer.h
    src/gea/demo/sdl/sdl_application.h
)
list(APPEND INL_${LIB}
    src/gea/demo/sdl/render/sdl_immediate_renderer.inl
)
list(APPEND SRC_${LIB}
    src/gea/demo/sdl/event/sdl_system_event_pump.cpp
    src/gea/demo/sdl/sdl_application.cpp
)

# force include of global header
force_include_header(global.h)

# organize source folders
source_group_ext(PREFIX "include" UNPREFIX "src" FILES ${INC_${LIB}})
source_group_ext(PREFIX "source"  UNPREFIX "src" FILES ${SRC_${LIB}} ${INL_${LIB}})

# add library and include directory
add_library(${LIB} STATIC ${SRC_${LIB}} ${INL_${LIB}} ${INC_${LIB}})
include_directories(${PROJECT_SOURCE_DIR} src)
target_include_directories(${LIB} PUBLIC src)

# add dependencies
target_link_libraries(${LIB} ${DEP_${LIB}})

# organize lib into solution folder
project_group(${LIB} "libs//demo")

# clean-up
unset(DEP_${LIB})
unset(INC_${LIB})
unset(INL_${LIB})
unset(SRC_${LIB})
