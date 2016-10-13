#################################################
# EXTERNAL: SFMT (patch)                        #
#################################################

cmake_minimum_required(VERSION 3.5)

set(LIB SFMT)

# source build variables
set(INC_${LIB} ) # include
set(SRC_${LIB} ) # source

# sfmt source
list(APPEND INC_${LIB}
	SFMT-alti.h
	SFMT-common.h
	SFMT-params.h
	SFMT-params11213.h
	SFMT-params1279.h
	SFMT-params132049.h
	SFMT-params19937.h
	SFMT-params216091.h
	SFMT-params2281.h
	SFMT-params4253.h
	SFMT-params44497.h
	SFMT-params607.h
	SFMT-params86243.h
	SFMT-sse2-msc.h
	SFMT-sse2.h
	SFMT.h
)
list(APPEND SRC_${LIB}
	SFMT.c
)

# organize source folders
source_group("include" FILES ${INC_${LIB}})
source_group("source"  FILES ${SRC_${LIB}} ${INL_${LIB}})

# add library
add_library(${LIB} STATIC ${SRC_${LIB}} ${INL_${LIB}} ${INC_${LIB}})

# install library and include headers
install(TARGETS ${LIB} ARCHIVE DESTINATION lib)
install(FILES ${INC_${LIB}} DESTINATION include)

# clean-up
unset(INC_${LIB})
unset(SRC_${LIB})
