#################################################
# LIB: GEA DATA                                 #
#################################################
set(LIB gea_data)

message(STATUS "Building ${LIB}")

# list dependencies
set(DEP_${LIB}
    gea_core
    gea_math
    gea_random
)

# source build variables
set(INC_${LIB}) # include
set(INL_${LIB}) # inline
set(SRC_${LIB}) # source

# list source
list(APPEND INC_${LIB}
    src/gea/data/core/guid.h
    src/gea/data/stream/bit_stream.h
    src/gea/data/stream/fixed_stream.h
    src/gea/data/stream/io_stream.h
)
list(APPEND INL_${LIB}
    src/gea/data/core/guid.inl
    src/gea/data/stream/bit_stream.inl
    src/gea/data/stream/fixed_stream.inl
)
list(APPEND SRC_${LIB}
    src/gea/data/stream/bit_stream.cpp
    src/gea/data/stream/fixed_stream.cpp
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

#################################################
# TEST: GEA DATA                                #
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
set(SRC_${LIB_TEST} ) # source

# core data
list(APPEND SRC_${LIB_TEST}
    test/gea/data/core/test_guid.cpp
    test/gea/data/stream/test_bit_stream.cpp
)

# force include of global header
force_include_header(global.h)

# organize source folders
source_group_ext(PREFIX "source" UNPREFIX "test" FILES ${SRC_${LIB_TEST}})

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
