#################################################
# LIB: GEA MATH GRAPH                           #
#################################################

set(LIB gea_math_graph)

message(STATUS "Building ${LIB}")

# list dependencies
set(DEP_${LIB}
	gea_math
)

# source build variables
set(INC_${LIB} ) # include
set(INL_${LIB} ) # inline
set(SRC_${LIB} ) # source

# graph math
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

# force include of global header
force_include_header(global.h)

# organize source folders
source_group("include" FILES ${INC_${LIB}})
source_group("source" FILES ${SRC_${LIB}} ${INL_${LIB}})

# add library and include directory
add_library(${LIB} STATIC ${SRC_${LIB}} ${INL_${LIB}} ${INC_${LIB}})
include_directories(${PROJECT_SOURCE_DIR} src)
target_include_directories(${LIB} PUBLIC src)

# add dependencies
target_link_libraries(${LIB} ${DEP_${LIB}})

# organize lib into solution folder
project_group(${LIB} "libs")

# Clean-up
unset(INC_${LIB})
unset(INL_${LIB})
unset(SRC_${LIB})
unset(DEP_${LIB})

#################################################
# TEST: GEA MATH GRAPH                          #
#################################################

set(LIB_TEST test_${LIB})

message(STATUS "Building ${LIB_TEST}")

# list dependencies
set(DEP_${LIB_TEST}
    ${LIB}
    ext_gtest
    ext_gtest_main
)

# source build variables
set(SRC_${LIB} ) # source

# core math
list(APPEND SRC_${LIB_TEST}
    test/gea/mth_graph/algorithm/test_point_reduce_rdp.cpp
    test/gea/mth_graph/algorithm/test_sampler.cpp
)

# force include of global header
force_include_header(global.h)

# organize source folders
source_group("source" FILES ${SRC_${LIB_TEST}})

# add target and test
add_executable(${LIB_TEST} ${SRC_${LIB_TEST}})
add_test(NAME ${LIB_TEST} COMMAND ${LIB_TEST})

# add dependencies
target_link_libraries(${LIB_TEST} ${DEP_${LIB_TEST}})

# organize lib into solution folder
project_group(${LIB_TEST} "tests")

# clean-up
unset(DEP_${LIB_TEST})
unset(SRC_${LIB_TEST})
