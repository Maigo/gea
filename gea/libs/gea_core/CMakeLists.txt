#################################################
# LIB: GEA CORE                                 #
#################################################
set(LIB gea_core)

message(STATUS "Building ${LIB}")

# list dependencies
set(DEP_${LIB}
)

# source build variables
set(INC_${LIB}) # include
set(INL_${LIB}) # inline
set(SRC_${LIB}) # source

# list source
list(APPEND INC_${LIB}
    src/gea/core/endian_base.h
    src/gea/system/platform.h
    src/gea/system/platform_win32.h
    src/gea/system/platform_intrinsic.h
    src/gea/utility/assert.h
)
list(APPEND INL_${LIB}
    src/gea/system/platform_intrinsic.inl
    
    src/gea/system/platform_win32.inl
    
    src/gea/utility/assert.inl
)
list(APPEND SRC_${LIB}
    src/module.cpp
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
project_group(${LIB} "libs")

# clean-up
unset(INC_${LIB})
unset(INL_${LIB})
unset(SRC_${LIB})
unset(DEP_${LIB})
