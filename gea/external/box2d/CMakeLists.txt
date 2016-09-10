include(ExternalProject)

#################################################
# LIB: BOX2D                                    #
#################################################
set(LIB ext_box2d)

message(STATUS "Building ${LIB}")

set(BOX2D_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/generated")

set(BOX2D_BUILD_SHARED ON)
set(BOX2D_BUILD_STATIC ON)
set(BOX2D_BUILD_EXAMPLES OFF)

ExternalProject_Add(BOX2D
	# DEPENDS
	PREFIX			${BOX2D_PREFIX}
	TMP_DIR			${BOX2D_PREFIX}/temp
	STAMP_DIR		${BOX2D_PREFIX}/stamp
	#--Download step--------------
	DOWNLOAD_DIR	${BOX2D_PREFIX}/download
	URL				https://github.com/erincatto/Box2D/archive/v2.3.1.zip
	URL_MD5			67fecbbaae23abcd4c8b0b91f82d59b4
#	GIT_REPOSITORY	https://github.com/erincatto/Box2D.git
#	GIT_TAG			v2.3.1
	#--Update/Patch step----------
	UPDATE_COMMAND	""
	#--Configure step-------------
	SOURCE_DIR		${BOX2D_PREFIX}/source
	CONFIGURE_COMMAND
					${CMAKE_COMMAND}
					"-H${BOX2D_PREFIX}/source/Box2D"
					"-B${BOX2D_PREFIX}/build"
	CMAKE_ARGS		-DCMAKE_INSTALL_PREFIX:PATH=${BOX2D_PREFIX}/install
					-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
					-DBUILD_SHARED_LIBS=${BUILD_SHARED_LIBS}
	#--Build step-----------------
	BINARY_DIR		${BOX2D_PREFIX}/build
	BUILD_COMMAND
					${CMAKE_COMMAND} --build <BINARY_DIR> --config ${Configuration}
	#--Install step---------------
	INSTALL_DIR		${BOX2D_PREFIX}/install
	INSTALL_COMMAND
					${CMAKE_COMMAND} --build <BINARY_DIR> --target install --config ${Configuration}
)

# Organize lib into solution folder
project_group(BOX2D "external")

# Make sure include directory exists
#file(MAKE_DIRECTORY ${BOX2D_PREFIX}/install/include/BOX2D/)

# Add library and include directory
add_library(${LIB} SHARED IMPORTED GLOBAL)
set_property(TARGET ${LIB} PROPERTY IMPORTED_LOCATION ${BOX2D_PREFIX}/install/bin/${CMAKE_SHARED_LIBRARY_PREFIX}box2d${CMAKE_SHARED_LIBRARY_SUFFIX})
set_property(TARGET ${LIB} PROPERTY IMPORTED_IMPLIB ${BOX2D_PREFIX}/install/lib/${CMAKE_STATIC_LIBRARY_PREFIX}box2d${CMAKE_STATIC_LIBRARY_SUFFIX})
set_property(TARGET ${LIB} PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${BOX2D_PREFIX}/install/include/Box2D/)

add_dependencies(${LIB} BOX2D)

# Clean-up
unset(LIB)
