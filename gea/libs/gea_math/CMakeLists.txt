#################################################
# LIB: GEA MATH                                 #
#################################################

set(LIB gea_math)

message(STATUS "Building ${LIB}")

# source build variables
set(INC_${LIB} )
set(INL_${LIB} )
set(SRC_${LIB} )

# base math
list(APPEND INC_${LIB}
  src/gea/bmth/error/err_base.h
  src/gea/bmth/type/half.h
  src/gea/bmth/base.h
  src/gea/bmth/bits.h
  src/gea/bmth/endian_swap.h
  src/gea/bmth/intrinsic.h
)
list(APPEND INL_${LIB}
  src/gea/bmth/error/err_base.inl
  src/gea/bmth/type/half.inl
  src/gea/bmth/base.inl
  src/gea/bmth/bits.inl
  src/gea/bmth/endian_swap.inl
  src/gea/bmth/intrinsic.inl
)
list(APPEND SRC_${LIB}
  src/gea/bmth/type/half.cpp
)

# geometry math
list(APPEND INC_${LIB}
  src/gea/gmth/aabb.h
  src/gea/gmth/line.h
  src/gea/gmth/polygon.h
  src/gea/gmth/rectangle.h
  src/gea/gmth/triangle.h
)
list(APPEND INL_${LIB}
  src/gea/gmth/aabb.inl
)
list(APPEND SRC_${LIB}
)

# vector math
list(APPEND INC_${LIB}
  src/gea/vmth/compression/comp_quaternion.h
  src/gea/vmth/compression/comp_vector3.h
  src/gea/vmth/compression/quantitizer.h
  src/gea/vmth/error/err_matrix3.h
  src/gea/vmth/error/err_quaternion.h
  src/gea/vmth/error/err_vector3.h
  src/gea/vmth/endian_swap.h
  src/gea/vmth/matrix3.h
  src/gea/vmth/point2.h
  src/gea/vmth/point3.h
  src/gea/vmth/polar2.h
  src/gea/vmth/polar3.h
  src/gea/vmth/quaternion.h
  src/gea/vmth/random.h
  src/gea/vmth/vector2.h
  src/gea/vmth/vector3.h
)
list(APPEND INL_${LIB}
  src/gea/vmth/compression/comp_vector3.inl
  src/gea/vmth/error/err_quaternion.inl
  src/gea/vmth/error/err_vector3.inl
  src/gea/vmth/endian_swap.inl
  src/gea/vmth/matrix3.inl
  src/gea/vmth/point2.inl
  src/gea/vmth/point3.inl
  src/gea/vmth/polar2.inl
  src/gea/vmth/polar3.inl
  src/gea/vmth/quaternion.inl
  src/gea/vmth/random.inl
  src/gea/vmth/vector2.inl
  src/gea/vmth/vector3.inl
)
list(APPEND SRC_${LIB}
  src/gea/vmth/compression/comp_quaternion.cpp
  src/gea/vmth/compression/comp_vector3.cpp
  src/gea/vmth/matrix3.cpp
  src/gea/vmth/point2.cpp
  src/gea/vmth/point3.cpp
  src/gea/vmth/polar2.cpp
  src/gea/vmth/polar3.cpp
  src/gea/vmth/quaternion.cpp
  src/gea/vmth/vector2.cpp
  src/gea/vmth/vector3.cpp
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
