#################################################
# LIB: GEA RANDOM                               #
#################################################
set(LIB gea_random)

message(STATUS "Building ${LIB}")

# source build variables
set(INC_${LIB} )
set(INL_${LIB} )
set(SRC_${LIB} )

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
    src/gea/random/SFMT.c
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
