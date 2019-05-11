#################################################
# LIB: GEA DEMO GLFW                            #
#################################################

set(LIB gea_demo_glfw)

message(STATUS "Building ${LIB}")

# list dependencies
set(DEP_${LIB}
    gea_core
    gea_math
	gea_data_core
    gea_demo_core
    ext_glfw
    ext_glad
)

# source build variables
set(INC_${LIB} ) # include
set(INL_${LIB} ) # inline
set(SRC_${LIB} ) # source

# core
list(APPEND INC_${LIB}
    src/gea/demo/glfw/callback/glfw_callback_handler.h
    src/gea/demo/glfw/render/glfw_immediate_renderer.h
    src/gea/demo/glfw/render/render_queue.h
    src/gea/demo/glfw/render/render_primitives.h
    src/gea/demo/glfw/render/render_types.h
    src/gea/demo/glfw/glfw_application.h
)
list(APPEND INL_${LIB}
    src/gea/demo/glfw/render/glfw_immediate_renderer.inl
    src/gea/demo/glfw/render/render_primitives.inl
    src/gea/demo/glfw/render/render_queue.inl
)
list(APPEND SRC_${LIB}
    src/gea/demo/glfw/callback/glfw_callback_handler.cpp
    src/gea/demo/glfw/render/glfw_immediate_renderer.cpp
    src/gea/demo/glfw/glfw_application.cpp
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
copy_imported_targets(${LIB} ${DEP_${LIB}})

# organize lib into solution folder
project_group(${LIB} "libs//demo")

# clean-up
unset(DEP_${LIB})
unset(INC_${LIB})
unset(INL_${LIB})
unset(SRC_${LIB})
