include(ExternalProject)

#################################################
# LIB: GLFW                                     #
#################################################
set(LIB ext_glfw)

message(STATUS "Building ${LIB}")

set(GLFW_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/generated")

set(BUILD_SHARED_LIBS ON)

ExternalProject_Add(GLFW
	# DEPENDS
	PREFIX			${GLFW_PREFIX}
	TMP_DIR			${GLFW_PREFIX}/temp
	STAMP_DIR		${GLFW_PREFIX}/stamp
	#--Download step--------------
	DOWNLOAD_DIR	${GLFW_PREFIX}/download
	URL				https://github.com/glfw/glfw/releases/download/3.2.1/glfw-3.2.1.zip
	URL_MD5			824c99eea073bdd6d2fec76b538f79af
#	GIT_REPOSITORY	https://github.com/glfw/glfw.git
#	GIT_TAG			3.2.1
	#--Update/Patch step----------
	UPDATE_COMMAND ""
	#--Configure step-------------
	SOURCE_DIR		${GLFW_PREFIX}/source
	CMAKE_ARGS		-DCMAKE_INSTALL_PREFIX:PATH=${GLFW_PREFIX}/install
					-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
					-DBUILD_SHARED_LIBS=${BUILD_SHARED_LIBS}
	#--Build step-----------------
	BINARY_DIR		${GLFW_PREFIX}/build
	BUILD_COMMAND
					${CMAKE_COMMAND} --build <BINARY_DIR> --config ${Configuration}
	#--Install step---------------
	INSTALL_DIR		${GLFW_PREFIX}/install
	INSTALL_COMMAND
					${CMAKE_COMMAND} --build <BINARY_DIR> --target install --config ${Configuration}
)

# Organize lib into solution folder
project_group(GLFW "external")

# Make sure include directory exists
file(MAKE_DIRECTORY ${GLFW_PREFIX}/install/include/GLFW/)

# Add library and include directory
add_library(${LIB} SHARED IMPORTED GLOBAL)
set_property(TARGET ${LIB} PROPERTY IMPORTED_LOCATION ${GLFW_PREFIX}/install/bin/${CMAKE_SHARED_LIBRARY_PREFIX}glfw3${CMAKE_SHARED_LIBRARY_SUFFIX})
set_property(TARGET ${LIB} PROPERTY IMPORTED_IMPLIB ${GLFW_PREFIX}/install/lib/${CMAKE_STATIC_LIBRARY_PREFIX}glfw3${CMAKE_STATIC_LIBRARY_SUFFIX})
set_property(TARGET ${LIB} PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${GLFW_PREFIX}/install/include/GLFW/)
set_property(TARGET ${LIB} PROPERTY INTERFACE_LINK_LIBRARIES ${GLFW_PREFIX}/install/lib/${CMAKE_STATIC_LIBRARY_PREFIX}glfw3dll${CMAKE_STATIC_LIBRARY_SUFFIX})

add_dependencies(${LIB} GLFW)

# Clean-up
unset(LIB)
