#################################################
# LIB: GEA HASH                                 #
#################################################
set(LIB gea_hash)

message(STATUS "Building ${LIB}")

# list dependencies
set(DEP_${LIB}
    ext_murmur
)

# source build variables
set(INC_${LIB})
set(INL_${LIB})
set(SRC_${LIB})

# hash 
list(APPEND INC_${LIB}
    src/gea/hash/hash.h
)
list(APPEND INL_${LIB}
    src/gea/hash/hash.inl
)
list(APPEND SRC_${LIB}
    src/gea/hash/hash.cpp
    src/gea/hash/hash_murmur.cpp
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
