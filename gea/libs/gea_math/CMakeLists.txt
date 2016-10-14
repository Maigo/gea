#################################################
# LIB: GEA MATH                                 #
#################################################

set(LIB gea_math)

message(STATUS "Building ${LIB}")

# list dependencies
set(DEP_${LIB}
    gea_random
)

# source build variables
set(INC_${LIB} ) # include
set(INL_${LIB} ) # inline
set(SRC_${LIB} ) # source

# core math
list(APPEND INC_${LIB}
    src/gea/mth_core/error/err_base.h
    src/gea/mth_core/type/half.h
    src/gea/mth_core/sort/binary_search.h
    src/gea/mth_core/base.h
    src/gea/mth_core/bits.h
    src/gea/mth_core/endian_swap.h
    src/gea/mth_core/intrinsic.h
    src/gea/mth_core/limits.h
)
list(APPEND INL_${LIB}
    src/gea/mth_core/error/err_base.inl
    src/gea/mth_core/type/half.inl
    src/gea/mth_core/sort/binary_search.inl
    src/gea/mth_core/base.inl
    src/gea/mth_core/bits.inl
    src/gea/mth_core/endian_swap.inl
    src/gea/mth_core/intrinsic.inl
    src/gea/mth_core/limits.inl
)
list(APPEND SRC_${LIB}
    src/gea/mth_core/type/half.cpp
)

# geometry math
list(APPEND INC_${LIB}
    src/gea/mth_geometry/internal/modify2.h
    src/gea/mth_geometry/line2.h
    src/gea/mth_geometry/polygon2.h
    src/gea/mth_geometry/rectangle2.h
)
list(APPEND INL_${LIB}
    src/gea/mth_geometry/internal/modify2.inl
    src/gea/mth_geometry/line2.inl
    src/gea/mth_geometry/polygon2.inl
    src/gea/mth_geometry/rectangle2.inl
)
list(APPEND SRC_${LIB}
    src/gea/mth_geometry/line2.cpp
    src/gea/mth_geometry/polygon2.cpp
)

# vector math
list(APPEND INC_${LIB}
    src/gea/mth_vector/compression/comp_quaternion.h
    src/gea/mth_vector/compression/comp_vector3.h
    src/gea/mth_vector/compression/quantitizer.h
    src/gea/mth_vector/error/err_matrix3.h
    src/gea/mth_vector/error/err_quaternion.h
    src/gea/mth_vector/error/err_vector3.h
    src/gea/mth_vector/algorithm2.h
    src/gea/mth_vector/algorithm3.h
    src/gea/mth_vector/endian_swap.h
    src/gea/mth_vector/linear_transform2.h
    src/gea/mth_vector/matrix2.h
    src/gea/mth_vector/matrix3.h
    src/gea/mth_vector/point2.h
    src/gea/mth_vector/point3.h
    src/gea/mth_vector/polar2.h
    src/gea/mth_vector/polar3.h
    src/gea/mth_vector/quaternion.h
    src/gea/mth_vector/random2.h
    src/gea/mth_vector/random3.h
    src/gea/mth_vector/vector2.h
    src/gea/mth_vector/vector3.h
)
list(APPEND INL_${LIB}
    src/gea/mth_vector/compression/comp_vector3.inl
    src/gea/mth_vector/error/err_quaternion.inl
    src/gea/mth_vector/error/err_vector3.inl
    src/gea/mth_vector/algorithm2.inl
    src/gea/mth_vector/algorithm3.inl
    src/gea/mth_vector/endian_swap.inl
    src/gea/mth_vector/linear_transform2.inl
    src/gea/mth_vector/matrix2.inl
    src/gea/mth_vector/matrix3.inl
    src/gea/mth_vector/point2.inl
    src/gea/mth_vector/point3.inl
    src/gea/mth_vector/polar2.inl
    src/gea/mth_vector/polar3.inl
    src/gea/mth_vector/quaternion.inl
    src/gea/mth_vector/random2.inl
    src/gea/mth_vector/random3.inl
    src/gea/mth_vector/vector2.inl
    src/gea/mth_vector/vector3.inl
)
list(APPEND SRC_${LIB}
    src/gea/mth_vector/compression/comp_quaternion.cpp
    src/gea/mth_vector/compression/comp_vector3.cpp
    src/gea/mth_vector/matrix2.cpp
    src/gea/mth_vector/matrix3.cpp
    src/gea/mth_vector/point2.cpp
    src/gea/mth_vector/point3.cpp
    src/gea/mth_vector/polar2.cpp
    src/gea/mth_vector/polar3.cpp
    src/gea/mth_vector/quaternion.cpp
    src/gea/mth_vector/vector2.cpp
    src/gea/mth_vector/vector3.cpp
)

# visual math
list(APPEND INC_${LIB}
    src/gea/mth_visual/color.h
)
list(APPEND INL_${LIB}
    src/gea/mth_visual/color.inl
)
list(APPEND SRC_${LIB}
    src/gea/mth_visual/color.cpp
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
unset(DEP_${LIB})
unset(INC_${LIB})
unset(INL_${LIB})
unset(SRC_${LIB})

#################################################
# TEST: GEA MATH                                #
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

# core math
list(APPEND SRC_${LIB_TEST}
    test/gea/mth_core/sort/test_binary_search.cpp
    test/gea/mth_core/test_base.cpp
)

# geometry math
list(APPEND SRC_${LIB_TEST}
    test/gea/mth_geometry/test_line2.cpp
    test/gea/mth_geometry/test_polygon2.cpp
)

# vector math
list(APPEND SRC_${LIB_TEST}
    test/gea/mth_vector/test_algorithm2.cpp
    test/gea/mth_vector/test_point2.cpp
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
