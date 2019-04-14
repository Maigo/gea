include(ExternalProject)

#################################################
# LIB: RapidXML                                 #
#################################################
set(LIB ext_rapidxml)

message(STATUS "Building ${LIB}")

set(PATCH_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/patch")
set(RAPIDXML_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/generated")

ExternalProject_Add(RAPIDXML
	# DEPENDS
	PREFIX			${RAPIDXML_PREFIX}
	TMP_DIR			${RAPIDXML_PREFIX}/temp
	STAMP_DIR		${RAPIDXML_PREFIX}/stamp
	#--Download step--------------
	DOWNLOAD_DIR	${RAPIDXML_PREFIX}/download
	URL				https://netcologne.dl.sourceforge.net/project/rapidxml/rapidxml/rapidxml%201.13/rapidxml-1.13.zip
	URL_MD5			7b4b42c9331c90aded23bb55dc725d6a
	#--Update/Patch step----------
	UPDATE_COMMAND	""
    PATCH_COMMAND   ${CMAKE_COMMAND} -E copy_directory ${PATCH_PREFIX}/ ${RAPIDXML_PREFIX}/source/
	#--Configure step-------------
	SOURCE_DIR		${RAPIDXML_PREFIX}/source
	CMAKE_ARGS		-DCMAKE_INSTALL_PREFIX:PATH=${RAPIDXML_PREFIX}/install
					-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
					-DBUILD_SHARED_LIBS=${BUILD_SHARED_LIBS}
	#--Build step-----------------
	BINARY_DIR		${RAPIDXML_PREFIX}/build
	BUILD_COMMAND
					${CMAKE_COMMAND} --build <BINARY_DIR> --config ${Configuration}
	#--Install step---------------
	INSTALL_DIR		${RAPIDXML_PREFIX}/install
	INSTALL_COMMAND
					${CMAKE_COMMAND} --build <BINARY_DIR> --target install --config ${Configuration}
)

# Organize lib into solution folder
project_group(RAPIDXML "__external")

# Make sure include directory exists
file(MAKE_DIRECTORY ${RAPIDXML_PREFIX}/install/include/rapidxml)

# Add library and include directory
add_library(${LIB} INTERFACE IMPORTED GLOBAL)
set_property(TARGET ${LIB} PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${RAPIDXML_PREFIX}/install/include/)

#add_dependencies(${LIB} rapidxml)

# Clean-up
unset(LIB)
