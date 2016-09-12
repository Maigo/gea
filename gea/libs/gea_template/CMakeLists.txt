#################################################
# LIB: GEA TEMPLATE                             #
#################################################

set(LIB gea_template)

message(STATUS "Building ${LIB}")

# source build variables
set(INC_${LIB} ) # include
set(INL_${LIB} ) # inline
set(SRC_${LIB} ) # source

# core template
list(APPEND INC_${LIB}
    src/gea/template/type_traits.h
)
list(APPEND INL_${LIB}
    src/gea/template/type_traits.inl
)
list(APPEND SRC_${LIB}
    src/gea/template/__force_compile.cpp
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

# organize lib into solution folder
project_group(${LIB} "libs")

# clean-up
unset(DEP_${LIB})
unset(INC_${LIB})
unset(INL_${LIB})

#################################################
# TEST: GEA TEMPLATE                            #
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
    test/gea/template/test_type_traits.cpp
)

# geometry math
list(APPEND SRC_${LIB}
)

# vector math
list(APPEND SRC_${LIB}
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
