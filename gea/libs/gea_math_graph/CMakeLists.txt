#################################################
# LIB: GEA MATH GRAPH                           #
#################################################

set(LIB gea_math_graph)

message(STATUS "Building ${LIB}")

# List dependencies
set(DEP_${LIB}
	gea_math
)

# source build variables
set(INC_${LIB} )
set(INL_${LIB} )
set(SRC_${LIB} )

# base math
list(APPEND INC_${LIB}
  src/gea/mth_graph/algorithm/point_reduce_rdp.h
  src/gea/mth_graph/algorithm/sampler.h
)
list(APPEND INL_${LIB}
  src/gea/mth_graph/algorithm/point_reduce_rdp.inl
  src/gea/mth_graph/algorithm/sampler.inl
)
list(APPEND SRC_${LIB}
  src/gea/mth_graph/algorithm/point_reduce_rdp.cpp
  src/gea/mth_graph/algorithm/sampler.cpp
)

# Force include of global header
force_include_header(global.h)

# Organize source folders
source_group("include" FILES ${INC_${LIB}})
source_group("source" FILES ${SRC_${LIB}} ${INL_${LIB}})

# Add library and include directory
add_library(${LIB} STATIC ${SRC_${LIB}} ${INL_${LIB}} ${INC_${LIB}})
include_directories(${PROJECT_SOURCE_DIR} src)
target_include_directories(${LIB} PUBLIC src)

# Add dependencies
target_link_libraries(${LIB} ${DEP_${LIB}})

# Organize lib into solution folder
project_group(${LIB} "libs")

# Clean-up
unset(INC_${LIB})
unset(INL_${LIB})
unset(SRC_${LIB})
unset(DEP_${LIB})
unset(LIB)
