#################################################
# LIB: GEA STRING                               #
#################################################
set(LIB gea_string)

message(STATUS "Building ${LIB}")

# list dependencies
set(DEP_${LIB}
    gea_core
)

# source build variables
set(INC_${LIB})
set(INL_${LIB})
set(SRC_${LIB})

# hash
list(APPEND INC_${LIB}
    src/gea/string/unicode/encode/ascii.h
    src/gea/string/unicode/encode/encode.h
    src/gea/string/unicode/encode/ucs2.h
    src/gea/string/unicode/encode/ucs4.h
    src/gea/string/unicode/encode/unicode.h
    src/gea/string/unicode/encode/utf8.h
    src/gea/string/unicode/encode/utf16.h
    src/gea/string/unicode/encode/utf32.h
    src/gea/string/unicode/charset.h
    src/gea/string/unicode/charset_ascii.h
    src/gea/string/unicode/charset_ucs.h
    src/gea/string/unicode/charset_utf.h
#    src/gea/string/unicode/eastlstring.h
#    src/gea/string/unicode/string.h
)
list(APPEND INL_${LIB}
    src/gea/string/unicode/encode/ascii.inl
    src/gea/string/unicode/encode/encode.inl
    src/gea/string/unicode/encode/ucs2.inl
    src/gea/string/unicode/encode/ucs4.inl
    src/gea/string/unicode/encode/utf8.inl
    src/gea/string/unicode/charset_ascii.inl
    src/gea/string/unicode/charset_ucs.inl
    src/gea/string/unicode/charset_utf.inl
#    src/gea/string/unicode/string.inl
)
list(APPEND SRC_${LIB}
    src/gea/string/unicode/encode/ucs2.cpp
    src/gea/string/unicode/encode/ucs4.cpp
    src/gea/string/unicode/encode/utf8.cpp
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

#################################################
# TEST: GEA STRING                              #
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
set(SRC_${LIB_TEST}) # source

# core random
list(APPEND SRC_${LIB_TEST}
    test/gea/string/unicode/encode/test_ascii.cpp
#    test/gea/string/unicode/test_charset_ascii.cpp
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
