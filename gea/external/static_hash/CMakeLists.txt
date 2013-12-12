#################################################
# LIB: STATIC_HASH                              #
#################################################
set(LIB gea_static_hash)

message(STATUS "Building ${LIB}")

# Define source 
set(SRC_${LIB}
    src/static_hash.cpp
    src/static_hash.h
)

# Force include of global header
force_include_header(global.h)

# Add library and include directory
add_library(${LIB} STATIC ${SRC_${LIB}})
include_directories("${PROJECT_SOURCE_DIR}" src)

# Organize lib into solution folder
project_group(${LIB} "libs")

# Clean-up
unset(SRC_${LIB})
unset(LIB)
