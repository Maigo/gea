#################################################
# LIB: GEA MATH                                 #
#################################################

set(LIB gea_math)

message(STATUS "Building ${LIB}")

# source build variables
set(INC_${LIB} )
set(INL_${LIB} )
set(SRC_${LIB} )

# core math
list(APPEND INC_${LIB}
  src/gea/mth_core/error/err_base.h
  src/gea/mth_core/type/half.h
  src/gea/mth_core/base.h
  src/gea/mth_core/bits.h
  src/gea/mth_core/endian_swap.h
  src/gea/mth_core/intrinsic.h
)
list(APPEND INL_${LIB}
  src/gea/mth_core/error/err_base.inl
  src/gea/mth_core/type/half.inl
  src/gea/mth_core/base.inl
  src/gea/mth_core/bits.inl
  src/gea/mth_core/endian_swap.inl
  src/gea/mth_core/intrinsic.inl
)
list(APPEND SRC_${LIB}
  src/gea/mth_core/type/half.cpp
)

# geometry math
list(APPEND INC_${LIB}
  src/gea/mth_geometry/aabb.h
  src/gea/mth_geometry/line.h
  src/gea/mth_geometry/polygon.h
  src/gea/mth_geometry/rectangle.h
  src/gea/mth_geometry/triangle.h
)
list(APPEND INL_${LIB}
  src/gea/mth_geometry/aabb.inl
)
list(APPEND SRC_${LIB}
)

# vector math
list(APPEND INC_${LIB}
  src/gea/mth_vector/compression/comp_quaternion.h
  src/gea/mth_vector/compression/comp_vector3.h
  src/gea/mth_vector/compression/quantitizer.h
  src/gea/mth_vector/error/err_matrix3.h
  src/gea/mth_vector/error/err_quaternion.h
  src/gea/mth_vector/error/err_vector3.h
  src/gea/mth_vector/endian_swap.h
  src/gea/mth_vector/matrix3.h
  src/gea/mth_vector/point2.h
  src/gea/mth_vector/point3.h
  src/gea/mth_vector/polar2.h
  src/gea/mth_vector/polar3.h
  src/gea/mth_vector/quaternion.h
  src/gea/mth_vector/random.h
  src/gea/mth_vector/vector2.h
  src/gea/mth_vector/vector3.h
)
list(APPEND INL_${LIB}
  src/gea/mth_vector/compression/comp_vector3.inl
  src/gea/mth_vector/error/err_quaternion.inl
  src/gea/mth_vector/error/err_vector3.inl
  src/gea/mth_vector/endian_swap.inl
  src/gea/mth_vector/matrix3.inl
  src/gea/mth_vector/point2.inl
  src/gea/mth_vector/point3.inl
  src/gea/mth_vector/polar2.inl
  src/gea/mth_vector/polar3.inl
  src/gea/mth_vector/quaternion.inl
  src/gea/mth_vector/random.inl
  src/gea/mth_vector/vector2.inl
  src/gea/mth_vector/vector3.inl
)
list(APPEND SRC_${LIB}
  src/gea/mth_vector/compression/comp_quaternion.cpp
  src/gea/mth_vector/compression/comp_vector3.cpp
  src/gea/mth_vector/matrix3.cpp
  src/gea/mth_vector/point2.cpp
  src/gea/mth_vector/point3.cpp
  src/gea/mth_vector/polar2.cpp
  src/gea/mth_vector/polar3.cpp
  src/gea/mth_vector/quaternion.cpp
  src/gea/mth_vector/vector2.cpp
  src/gea/mth_vector/vector3.cpp
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

# Organize lib into solution folder
project_group(${LIB} "libs")

# Clean-up
unset(INC_${LIB})
unset(INL_${LIB})
unset(SRC_${LIB})
unset(LIB)
