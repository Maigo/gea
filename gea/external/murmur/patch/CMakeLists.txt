cmake_minimum_required(VERSION 3.5)

#################################################
# EXTERNAL: MURMUR (patch)                      #
#################################################

set(LIB MURMUR)

# source build variables
set(INC_${LIB}) # include
set(SRC_${LIB}) # source

# sfmt source
list(APPEND INC_${LIB}
    src/MurMurHash1.h
    src/MurMurHash2.h
    src/MurMurHash3.h
)
list(APPEND SRC_${LIB}
    src/MurMurHash1.cpp
    src/MurMurHash2.cpp
    src/MurMurHash3.cpp
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
