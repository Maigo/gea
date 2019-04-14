include(ExternalProject)

#################################################
# LIB: GOOGLE TEST                              #
#################################################
set(LIB_GTEST		ext_gtest)
set(LIB_GTEST_MAIN	ext_gtest_main)
set(LIB_GMOCK		ext_gmock)
set(LIB_GMOCK_MAIN	ext_gmock_main)

message(STATUS "Building ${LIB_GTEST}")
message(STATUS "Building ${LIB_GTEST_MAIN}")
message(STATUS "Building ${LIB_GMOCK}")
message(STATUS "Building ${LIB_GMOCK_MAIN}")
message(STATUS "CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS}")

set(GTEST_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/generated")

set(gtest_force_shared_crt ON)

# disable warnings
set(CMAKE_CXX_FLAGS_EXTERNAL "${CMAKE_CXX_FLAGS} /wd4996")

ExternalProject_Add(GTEST
	# DEPENDS
	PREFIX			${GTEST_PREFIX}
	TMP_DIR			${GTEST_PREFIX}/temp
	STAMP_DIR		${GTEST_PREFIX}/stamp
	#--Download step--------------
	DOWNLOAD_DIR	${GTEST_PREFIX}/download
	URL				https://github.com/google/googletest/archive/release-1.8.1.zip
	URL_MD5			ad6868782b5952b7476a7c1c72d5a714
	#--Update/Patch step----------
	UPDATE_COMMAND	""
	#--Configure step-------------
	SOURCE_DIR		${GTEST_PREFIX}/source
	CMAKE_ARGS		-DCMAKE_INSTALL_PREFIX:PATH=${GTEST_PREFIX}/install
					-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
					-DBUILD_SHARED_LIBS=${BUILD_SHARED_LIBS}
					-DCMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS_EXTERNAL}
					-Dgtest_force_shared_crt=${gtest_force_shared_crt}
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
project_group(GTEST "__external")

# Make sure include directory exists
file(MAKE_DIRECTORY ${GTEST_PREFIX}/install/include/)

# Add library and include directory
if (BUILD_SHARED_LIBS)
	add_library(${LIB_GTEST} SHARED IMPORTED GLOBAL)
	set_property(TARGET ${LIB_GTEST} PROPERTY IMPORTED_LOCATION						${GTEST_PREFIX}/install/lib/${CMAKE_SHARED_LIBRARY_PREFIX}gtest${CMAKE_SHARED_LIBRARY_SUFFIX})
	set_property(TARGET ${LIB_GTEST} PROPERTY IMPORTED_IMPLIB						${GTEST_PREFIX}/install/lib/${CMAKE_STATIC_LIBRARY_PREFIX}gtest${CMAKE_STATIC_LIBRARY_SUFFIX})
	set_property(TARGET ${LIB_GTEST} PROPERTY INTERFACE_INCLUDE_DIRECTORIES			${GTEST_PREFIX}/install/include/)

	add_library(${LIB_GTEST_MAIN} SHARED IMPORTED GLOBAL)
	set_property(TARGET ${LIB_GTEST_MAIN} PROPERTY IMPORTED_LOCATION				${GTEST_PREFIX}/install/lib/${CMAKE_SHARED_LIBRARY_PREFIX}gtest_main${CMAKE_SHARED_LIBRARY_SUFFIX})
	set_property(TARGET ${LIB_GTEST_MAIN} PROPERTY IMPORTED_IMPLIB					${GTEST_PREFIX}/install/lib/${CMAKE_STATIC_LIBRARY_PREFIX}gtest_main${CMAKE_STATIC_LIBRARY_SUFFIX})
	set_property(TARGET ${LIB_GTEST_MAIN} PROPERTY INTERFACE_INCLUDE_DIRECTORIES	${GTEST_PREFIX}/install/include/)
else (BUILD_SHARED_LIBS)
	add_library(${LIB_GTEST} STATIC IMPORTED GLOBAL)
	set_property(TARGET ${LIB_GTEST} PROPERTY IMPORTED_LOCATION						${GTEST_PREFIX}/install/lib/${CMAKE_STATIC_LIBRARY_PREFIX}gtest${CMAKE_STATIC_LIBRARY_SUFFIX})
	set_property(TARGET ${LIB_GTEST} PROPERTY INTERFACE_INCLUDE_DIRECTORIES			${GTEST_PREFIX}/install/include/)

	add_library(${LIB_GTEST_MAIN} STATIC IMPORTED GLOBAL)
	set_property(TARGET ${LIB_GTEST_MAIN} PROPERTY IMPORTED_LOCATION				${GTEST_PREFIX}/install/lib/${CMAKE_STATIC_LIBRARY_PREFIX}gtest_main${CMAKE_STATIC_LIBRARY_SUFFIX})
	set_property(TARGET ${LIB_GTEST_MAIN} PROPERTY INTERFACE_INCLUDE_DIRECTORIES	${GTEST_PREFIX}/install/include/)
endif (BUILD_SHARED_LIBS)

if (BUILD_SHARED_LIBS)
	add_library(${LIB_GMOCK} SHARED IMPORTED GLOBAL)
	set_property(TARGET ${LIB_GMOCK} PROPERTY IMPORTED_LOCATION						${GTEST_PREFIX}/install/lib/${CMAKE_SHARED_LIBRARY_PREFIX}gmock${CMAKE_SHARED_LIBRARY_SUFFIX})
	set_property(TARGET ${LIB_GMOCK} PROPERTY IMPORTED_IMPLIB						${GTEST_PREFIX}/install/lib/${CMAKE_STATIC_LIBRARY_PREFIX}gmock${CMAKE_STATIC_LIBRARY_SUFFIX})
	set_property(TARGET ${LIB_GMOCK} PROPERTY INTERFACE_INCLUDE_DIRECTORIES			${GTEST_PREFIX}/install/include/)

	add_library(${LIB_GMOCK_MAIN} SHARED IMPORTED GLOBAL)
	set_property(TARGET ${LIB_GMOCK_MAIN} PROPERTY IMPORTED_LOCATION				${GTEST_PREFIX}/install/lib/${CMAKE_SHARED_LIBRARY_PREFIX}gmock_main${CMAKE_SHARED_LIBRARY_SUFFIX})
	set_property(TARGET ${LIB_GMOCK_MAIN} PROPERTY IMPORTED_IMPLIB					${GTEST_PREFIX}/install/lib/${CMAKE_STATIC_LIBRARY_PREFIX}gmock_main${CMAKE_STATIC_LIBRARY_SUFFIX})
	set_property(TARGET ${LIB_GMOCK_MAIN} PROPERTY INTERFACE_INCLUDE_DIRECTORIES	${GTEST_PREFIX}/install/include/)
else (BUILD_SHARED_LIBS)
	add_library(${LIB_GMOCK} STATIC IMPORTED GLOBAL)
	set_property(TARGET ${LIB_GMOCK} PROPERTY IMPORTED_LOCATION						${GTEST_PREFIX}/install/lib/${CMAKE_STATIC_LIBRARY_PREFIX}gmock${CMAKE_STATIC_LIBRARY_SUFFIX})
	set_property(TARGET ${LIB_GMOCK} PROPERTY INTERFACE_INCLUDE_DIRECTORIES			${GTEST_PREFIX}/install/include/)

	add_library(${LIB_GMOCK_MAIN} STATIC IMPORTED GLOBAL)
	set_property(TARGET ${LIB_GMOCK_MAIN} PROPERTY IMPORTED_LOCATION				${GTEST_PREFIX}/install/lib/${CMAKE_STATIC_LIBRARY_PREFIX}gmock_main${CMAKE_STATIC_LIBRARY_SUFFIX})
	set_property(TARGET ${LIB_GMOCK_MAIN} PROPERTY INTERFACE_INCLUDE_DIRECTORIES	${GTEST_PREFIX}/install/include/)
endif (BUILD_SHARED_LIBS)

add_dependencies(${LIB_GTEST}		GTEST)
add_dependencies(${LIB_GTEST_MAIN}	${LIB_GTEST})
add_dependencies(${LIB_GMOCK}		${LIB_GTEST})
add_dependencies(${LIB_GMOCK_MAIN}	${LIB_GMOCK})

# Clean-up
unset(LIB)
