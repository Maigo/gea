#################################################
# LIB: GEA EASTL                                #
#################################################

set(LIB gea_eastl)

message(STATUS "Building ${LIB}")

# source build variables
set(INC_${LIB} )
set(INL_${LIB} )
set(SRC_${LIB} )

list(APPEND INC_${LIB}
  src/eastl/internal/fixed_pool.h
  src/eastl/fixed_vector.h
  src/eastl/memory.h
  src/eastl/vector.h
)
list(APPEND INL_${LIB}
  src/eastl/fixed_vector.inl
  src/eastl/memory.inl
  src/eastl/vector.inl
)
list(APPEND SRC_${LIB}
)

# Force include of global header
force_include_header(global.h)

# Organize source folders
source_group_ext(PREFIX "include" UNPREFIX "src" FILES ${INC_${LIB}})
source_group_ext(PREFIX "source"  UNPREFIX "src" FILES ${SRC_${LIB}} ${INL_${LIB}})

# Add library and include directory
add_library(${LIB} STATIC ${SRC_${LIB}} ${INL_${LIB}} ${INC_${LIB}})
include_directories(${PROJECT_SOURCE_DIR} src)
target_include_directories(${LIB} PUBLIC src)

# Force linker language to C++ (header onlly lib)
set_target_properties(${LIB} PROPERTIES LINKER_LANGUAGE CXX)

# Organize lib into solution folder
project_group(${LIB} "libs")

# Clean-up
unset(INC_${LIB})
unset(INL_${LIB})
unset(SRC_${LIB})
unset(LIB)
