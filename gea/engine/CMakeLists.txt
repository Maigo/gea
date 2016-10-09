#################################################
# LIB: ENGINE                                   #
#################################################

set(LIB gea_engine)

message(STATUS "Building ${LIB}")

# List dependencies
set(DEP_${LIB}
    gea_math
)

# source build variables
set(INC_${LIB} ) # include
set(INL_${LIB} ) # inline
set(SRC_${LIB} ) # source

# List source
list(APPEND INC_${LIB}
    src/gea/core/error/error_codes.h
    src/gea/core/memory/allocator.h
    src/gea/core/memory/allocator_chunk.h
    src/gea/core/memory/allocator_heap.h
    src/gea/core/memory/allocator_linear.h
    src/gea/core/memory/allocator_linked.h
    src/gea/core/memory/allocator_manager.h
    src/gea/core/memory/allocator_page.h
    src/gea/core/memory/allocator_pool.h
    src/gea/core/memory/allocator_proxy.h
    src/gea/core/memory/memory.h
#   src/gea/core/parallel/task.h
#   src/gea/core/parallel/task_manager.h
    src/gea/core/pattern/singleton.h
    src/gea/core/application.h
    src/gea/core/endian_base.h
    src/gea/core/idstring.h
    src/gea/core/time_scheme.h
)
list(APPEND INL_${LIB}
    src/gea/core/memory/allocator.inl
    src/gea/core/memory/allocator_heap.inl
    src/gea/core/memory/allocator_linear.inl
    src/gea/core/memory/allocator_linked.inl
    src/gea/core/memory/allocator_manager.inl
    src/gea/core/memory/allocator_page.inl
#   src/gea/core/parallel/task_manager.inl
    src/gea/core/pattern/singleton.inl
    src/gea/core/idstring.inl
    src/gea/core/time_scheme.inl
)
list(APPEND SRC_${LIB}
    src/gea/core/memory/allocator_chunk.cpp
    src/gea/core/memory/allocator_heap.cpp
    src/gea/core/memory/allocator_linear.cpp
    src/gea/core/memory/allocator_linked.cpp
    src/gea/core/memory/allocator_page.cpp
    src/gea/core/memory/allocator_pool.cpp
    src/gea/core/memory/allocator_proxy.cpp
#   src/gea/core/parallel/task_manager.cpp
    src/gea/core/application.cpp
    src/gea/core/time_scheme.cpp
)

# Force include of global header
force_include_header(global.h)

# Organize source files into folders
source_group_ext(PREFIX "include" UNPREFIX "src" FILES ${INC_${LIB}})
source_group_ext(PREFIX "source"  UNPREFIX "src" FILES ${SRC_${LIB}} ${INL_${LIB}})

# Add library and include directory
add_library(${LIB} STATIC ${SRC_${LIB}})
include_directories(${PROJECT_SOURCE_DIR} src)
target_include_directories(${LIB} PUBLIC src)

# Add dependencies
target_link_libraries(${LIB} ${DEP_${LIB}})

# Organize lib into solution folder
project_group(${LIB} "libs")

# Clean-up
unset(SRC_${LIB})
unset(DEP_${LIB})
unset(LIB)
