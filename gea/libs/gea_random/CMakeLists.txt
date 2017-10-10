#################################################
# LIB: GEA RANDOM                               #
#################################################
set(LIB gea_random)

message(STATUS "Building ${LIB}")

# list dependencies
set(DEP_${LIB}
    ext_sfmt
)

# list precompiled defines
set(DEF_${LIB}
    SFMT_MEXP=19937
)

# source build variables
set(INC_${LIB})
set(INL_${LIB})
set(SRC_${LIB})

# random
list(APPEND INC_${LIB}
    src/gea/random/random.h
)
list(APPEND INL_${LIB}
    src/gea/random/random.inl
)
list(APPEND SRC_${LIB}
    src/gea/random/random.cpp
    src/gea/random/random_sfmt.cpp
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

# set precompiled defines
target_compile_definitions(${LIB} PRIVATE ${DEF_${LIB}})

# add dependencies
target_link_libraries(${LIB} ${DEP_${LIB}})

# organize lib into solution folder
project_group(${LIB} "libs")

# clean-up
unset(INC_${LIB})
unset(INL_${LIB})
unset(SRC_${LIB})

#################################################
# TEST: GEA RANDOM
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

# core random
list(APPEND SRC_${LIB_TEST}
    test/gea/random/test_random.cpp
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
