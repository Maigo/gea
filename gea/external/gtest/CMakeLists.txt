include(ExternalProject)

#################################################
# LIB: GOOGLE TEST                              #
#################################################
set(LIB ext_gtest)

message(STATUS "Building ${LIB}")

set(GTEST_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/generated")

set(SDL_BUILDING_LIBRARY ON)

ExternalProject_Add(GTEST
	# DEPENDS
	PREFIX			${GTEST_PREFIX}
	TMP_DIR			${GTEST_PREFIX}/temp
	STAMP_DIR		${GTEST_PREFIX}/stamp
	#--Download step--------------
	DOWNLOAD_DIR	${GTEST_PREFIX}/download
	URL				https://github.com/google/googletest/archive/release-1.8.0.zip
	URL_MD5			adfafc8512ab65fd3cf7955ef0100ff5
	#--Update/Patch step----------
	UPDATE_COMMAND	""
	#--Configure step-------------
	SOURCE_DIR		${GTEST_PREFIX}/source
	CMAKE_ARGS		-DCMAKE_INSTALL_PREFIX:PATH=${GTEST_PREFIX}/install
					-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
					-DBUILD_SHARED_LIBS=${BUILD_SHARED_LIBS}
	#--Build step-----------------
	BINARY_DIR		${GTEST_PREFIX}/build
	BUILD_COMMAND
					${CMAKE_COMMAND} --build <BINARY_DIR> --config ${Configuration}
	#--Install step---------------
	INSTALL_DIR		${GTEST_PREFIX}/install
	INSTALL_COMMAND
					${CMAKE_COMMAND} --build <BINARY_DIR> --target install --config ${Configuration}
)

# Organize lib into solution folder
project_group(GTEST "external")

# Make sure include directory exists
file(MAKE_DIRECTORY ${GTEST_PREFIX}/install/include/gtest/)
file(MAKE_DIRECTORY ${GTEST_PREFIX}/install/include/gmock/)

# Add library and include directory
add_library(${LIB} STATIC IMPORTED GLOBAL)
set_property(TARGET ${LIB} PROPERTY IMPORTED_LOCATION ${GTEST_PREFIX}/install/bin/${CMAKE_STATIC_LIBRARY_PREFIX}gtest${CMAKE_STATIC_LIBRARY_SUFFIX})
set_property(TARGET ${LIB} PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${GTEST_PREFIX}/install/include/gtest/ ${GTEST_PREFIX}/install/include/gmock/)
set_property(TARGET ${LIB} PROPERTY INTERFACE_LINK_LIBRARIES ${GTEST_PREFIX}/install/lib/${CMAKE_STATIC_LIBRARY_PREFIX}gtest_main${CMAKE_STATIC_LIBRARY_SUFFIX})
set_property(TARGET ${LIB} PROPERTY INTERFACE_LINK_LIBRARIES ${GTEST_PREFIX}/install/lib/${CMAKE_STATIC_LIBRARY_PREFIX}gmock${CMAKE_STATIC_LIBRARY_SUFFIX})
set_property(TARGET ${LIB} PROPERTY INTERFACE_LINK_LIBRARIES ${GTEST_PREFIX}/install/lib/${CMAKE_STATIC_LIBRARY_PREFIX}gmock_main${CMAKE_STATIC_LIBRARY_SUFFIX})

add_dependencies(${LIB} GTEST)

# Clean-up
unset(LIB)
