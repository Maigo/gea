#################################################
# LIB: GEA CORE                                 #
#################################################
set(LIB gea_core)

message(STATUS "Building ${LIB}")

# enable assembly support
enable_language(ASM_MASM)

# list dependencies
set(DEP_${LIB}
)

# source build variables
set(INC_${LIB}) # include
set(INL_${LIB}) # inline
set(SRC_${LIB}) # source
set(ASM_${LIB}) # assembly

# list source
list(APPEND INC_${LIB}
	src/gea/core/bits/bsa.h
	src/gea/core/bits/bcl.h
	src/gea/core/bits/bits.h
	src/gea/core/bits/flag.h
	src/gea/core/pattern/delegate.h
	src/gea/core/pattern/delegate_base.h
	src/gea/core/pattern/delegate_multicast.h
	src/gea/core/pattern/either.h
	src/gea/core/pattern/maybe.h
	src/gea/core/pattern/member_delegate.h
	src/gea/core/pattern/singleton.h
	src/gea/core/pattern/static_block.h
	src/gea/core/string/string_builder.h
	src/gea/core/string/string_parser.h
	src/gea/core/string/string_util.h
	src/gea/core/endian_base.h
	src/gea/core/limits.h
	src/gea/core/math.h
	src/gea/core/type_traits.h
	src/gea/core/variable.h
	src/gea/system/memory/allocator/allocator.h
	src/gea/system/memory/allocator/allocator_chunk.h
	src/gea/system/memory/allocator/allocator_heap.h
	src/gea/system/memory/allocator/allocator_linear.h
	src/gea/system/memory/allocator/allocator_linked.h
	src/gea/system/memory/allocator/allocator_manager.h
	src/gea/system/memory/allocator/allocator_page.h
	src/gea/system/memory/allocator/allocator_pool.h
	src/gea/system/memory/allocator/allocator_proxy.h
	src/gea/system/memory/memory_virtual.h
	src/gea/system/memory/memory_virtual_win32.h
	src/gea/system/platform.h
	src/gea/system/platform_win32.h
	src/gea/system/platform_intrinsic.h
	src/gea/utility/assert.h
)
list(APPEND INL_${LIB}
	src/gea/core/bits/bsa.inl
	src/gea/core/bits/bcl.inl
	src/gea/core/bits/bits.inl
	src/gea/core/bits/flag.inl
	src/gea/core/pattern/delegate.inl
	src/gea/core/pattern/delegate_base.inl
	src/gea/core/pattern/delegate_multicast.inl
	src/gea/core/pattern/either.inl
	src/gea/core/pattern/maybe.inl
	src/gea/core/pattern/member_delegate.inl
	src/gea/core/pattern/singleton.inl
	src/gea/core/string/string_builder.inl
	src/gea/core/string/string_parser.inl
	src/gea/core/string/string_util.inl
	src/gea/core/math.inl
	src/gea/core/variable.inl
	src/gea/system/memory/allocator/allocator.inl
	src/gea/system/memory/allocator/allocator_heap.inl
	src/gea/system/memory/allocator/allocator_linear.inl
	src/gea/system/memory/allocator/allocator_linked.inl
	src/gea/system/memory/allocator/allocator_manager.inl
	src/gea/system/memory/allocator/allocator_page.inl
	src/gea/system/platform_intrinsic.inl
	src/gea/system/platform_win32.inl
	src/gea/utility/assert.inl
)
list(APPEND SRC_${LIB}
	src/gea/system/memory/allocator/allocator_chunk.cpp
	src/gea/system/memory/allocator/allocator_heap.cpp
	src/gea/system/memory/allocator/allocator_linear.cpp
	src/gea/system/memory/allocator/allocator_linked.cpp
	src/gea/system/memory/allocator/allocator_page.cpp
	src/gea/system/memory/allocator/allocator_pool.cpp
	src/gea/system/memory/allocator/allocator_proxy.cpp
	src/module.cpp
)
if(GEA_PLATFORM_BITNESS EQUAL 32)
	list(APPEND ASM_${LIB}
		src/gea/system/platform_intrinsic_ia32.asm
	)
	set_source_files_properties(${ASM_${LIB}} PROPERTIES COMPILE_FLAGS "/safeseh")
elseif(GEA_PLATFORM_BITNESS EQUAL 64)
	list(APPEND ASM_${LIB}
		src/gea/system/platform_intrinsic_ia64.asm
	)
endif()

# force include of global header
force_include_header(global.h)

# organize source folders
source_group_ext(PREFIX "include" UNPREFIX "src" FILES ${INC_${LIB}})
source_group_ext(PREFIX "source"  UNPREFIX "src" FILES ${SRC_${LIB}} ${INL_${LIB}} ${ASM_${LIB}})

# add library and include directory
add_library(${LIB} STATIC ${SRC_${LIB}} ${INL_${LIB}} ${INC_${LIB}} ${ASM_${LIB}})
include_directories(${PROJECT_SOURCE_DIR} src)
target_include_directories(${LIB} PUBLIC src)

# add dependencies
target_link_libraries(${LIB} ${DEP_${LIB}})

# organize lib into solution folder
project_group(${LIB} "libs//core")

# clean-up
unset(ASM_${LIB})
unset(INC_${LIB})
unset(INL_${LIB})
unset(SRC_${LIB})
unset(DEP_${LIB})

#################################################
# TEST: GEA CORE                                #
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

# core data
list(APPEND SRC_${LIB_TEST}
	test/gea/core/bits/test_bits.cpp
	test/gea/core/bits/test_flag.cpp
	test/gea/core/pattern/test_delegate.cpp
	test/gea/core/pattern/test_delegate_multicast.cpp
	test/gea/core/pattern/test_maybe.cpp
	test/gea/core/pattern/test_either.cpp
	test/gea/core/pattern/test_member_delegate.cpp
	test/gea/core/string/test_string_builder.cpp
	test/gea/core/string/test_string_util.cpp
	test/gea/core/test_endian_base.cpp
	test/gea/core/test_math.cpp
	test/gea/core/test_variable.cpp
	test/gea/system/test_platform_intrinsic.cpp
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
project_group(${LIB_TEST} "tests//core")

# clean-up
unset(DEP_${LIB_TEST})
unset(SRC_${LIB_TEST})
