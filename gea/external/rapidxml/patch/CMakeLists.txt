cmake_minimum_required(VERSION 3.5)

#################################################
# EXTERNAL: RapidXML (patch)                    #
#################################################

set(LIB rapidxml)

# source build variables
set(INC_${LIB}) # include

# rapidxml source
list(APPEND INC_${LIB}
    rapidxml.hpp
    rapidxml_iterators.hpp
    rapidxml_print.hpp
    rapidxml_utils.hpp
)

# add library
add_library(${LIB} INTERFACE)
target_include_directories(${LIB} INTERFACE include)

# install library and include headers
install(FILES ${INC_${LIB}} DESTINATION include/rapidxml)

# clean-up
unset(INC_${LIB})