#################################################
# LIB: ENGINE                                   #
#################################################

set(LIB gea_engine)

message(STATUS "Building ${LIB}")

# List dependencies
set(DEP_${LIB}
	gea_math
)

# List source
set(SRC_ENGINE_CORE_ERROR
	src/gea/core/error/error_codes.h
)
set(SRC_ENGINE_CORE_MEMORY
	src/gea/core/memory/allocator.h
	src/gea/core/memory/allocator.inl
	src/gea/core/memory/allocator_chunk.cpp
	src/gea/core/memory/allocator_chunk.h
	src/gea/core/memory/allocator_heap.cpp
	src/gea/core/memory/allocator_heap.h
	src/gea/core/memory/allocator_heap.inl
	src/gea/core/memory/allocator_linear.cpp
	src/gea/core/memory/allocator_linear.h
	src/gea/core/memory/allocator_linear.inl
	src/gea/core/memory/allocator_linked.cpp
	src/gea/core/memory/allocator_linked.h
	src/gea/core/memory/allocator_linked.inl
	src/gea/core/memory/allocator_manager.h
	src/gea/core/memory/allocator_manager.inl
	src/gea/core/memory/allocator_page.cpp
	src/gea/core/memory/allocator_page.h
	src/gea/core/memory/allocator_page.inl
	src/gea/core/memory/allocator_pool.cpp
	src/gea/core/memory/allocator_pool.h
	src/gea/core/memory/allocator_proxy.cpp
	src/gea/core/memory/allocator_proxy.h
	src/gea/core/memory/memory.h
)
set(SRC_ENGINE_CORE_PARALLEL
#	src/gea/core/parallel/task.h
#	src/gea/core/parallel/task_manager.cpp
#	src/gea/core/parallel/task_manager.h
#	src/gea/core/parallel/task_manager.inl
)
set(SRC_ENGINE_CORE_PATTERN
	src/gea/core/pattern/singleton.h
	src/gea/core/pattern/singleton.inl
)
set(SRC_ENGINE_CORE
	src/gea/core/application.cpp
	src/gea/core/application.h
	src/gea/core/endian_base.h
	src/gea/core/idstring.h
	src/gea/core/idstring.inl
	src/gea/core/time_scheme.cpp
	src/gea/core/time_scheme.h
	src/gea/core/time_scheme.inl
)

set(SRC_${LIB}
    ${SRC_ENGINE_CORE_ERROR}
    ${SRC_ENGINE_CORE_MEMORY}
    ${SRC_ENGINE_CORE_PARALLEL}
    ${SRC_ENGINE_CORE_PATTERN}
    ${SRC_ENGINE_CORE}
)

# Force include of global header
force_include_header(global.h)

# Organize source files into folders
source_group("engine\\core\\error"    FILES ${SRC_ENGINE_CORE_ERROR})
source_group("engine\\core\\memory"   FILES ${SRC_ENGINE_CORE_MEMORY})
source_group("engine\\core\\parallel" FILES ${SRC_ENGINE_CORE_PARALLEL})
source_group("engine\\core\\pattern"  FILES ${SRC_ENGINE_CORE_PATTERN})
source_group("engine\\core"           FILES ${SRC_ENGINE_CORE})

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
