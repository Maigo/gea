#################################################
# LIB: GEA DATA FORMAT CLI                      #
#################################################
set(LIB gea_data_format_cli)

message(STATUS "Building ${LIB}")

# list dependencies
set(DEP_${LIB}
    gea_core
    gea_hash
    gea_data_core
)

# source build variables
set(INC_${LIB}) # include
set(INL_${LIB}) # inline
set(SRC_${LIB}) # source

# list source
list(APPEND INC_${LIB}
    src/gea/data/cli/cli_debug.h
    src/gea/data/cli/cli_lexer.h
    src/gea/data/cli/cli_parser.h
)
list(APPEND INL_${LIB}
    src/gea/data/cli/cli_debug.inl
    src/gea/data/cli/cli_lexer.inl
    src/gea/data/cli/cli_parser.inl
)
list(APPEND SRC_${LIB}
    src/gea/data/cli/cli_lexer.cpp
    src/gea/data/cli/cli_parser.cpp
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
project_group(${LIB} "libs//data//format")

# clean-up
unset(INC_${LIB})
unset(INL_${LIB})
unset(SRC_${LIB})
unset(DEP_${LIB})

#################################################
# TEST: GEA DATA FORMAT CLI                     #
#################################################

set(LIB_TEST test_${LIB})

message(STATUS "Building ${LIB_TEST}")

# list dependencies
set(DEP_${LIB_TEST}
    ${LIB}
    ext_gtest
    ext_gtest_main
    gea_core
)

# source build variables
set(SRC_${LIB_TEST} ) # source

# source tests
list(APPEND SRC_${LIB_TEST}
    test/gea/data/cli/test_cli_lexer.cpp
    test/gea/data/cli/test_cli_parser.cpp
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
project_group(${LIB_TEST} "tests//data//format")

# clean-up
unset(DEP_${LIB_TEST})
unset(SRC_${LIB_TEST})
