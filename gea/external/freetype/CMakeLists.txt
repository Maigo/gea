include(ExternalProject)

#################################################
# LIB: FREETYPE                                 #
#################################################
set(LIB ext_freetype)

message(STATUS "Building ${LIB}")

set(FREETYPE_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/generated")

ExternalProject_Add(FREETYPE
    # DEPENDS
    PREFIX          ${FREETYPE_PREFIX}
    TMP_DIR         ${FREETYPE_PREFIX}/temp
    STAMP_DIR       ${FREETYPE_PREFIX}/stamp
    #--Download step--------------
    DOWNLOAD_DIR    ${FREETYPE_PREFIX}/download
#   URL             http://download.savannah.gnu.org/releases/freetype/freetype-2.7.tar.gz
#   URL_MD5         337139e5c7c5bd645fe130608e0fa8b5
    GIT_REPOSITORY  http://git.savannah.nongnu.org/r/freetype/freetype2.git/
    GIT_TAG         VER-2-7
    #--Update/Patch step----------
    UPDATE_COMMAND  ""
    #--Configure step-------------
    SOURCE_DIR      ${FREETYPE_PREFIX}/source
    CMAKE_ARGS      -DCMAKE_INSTALL_PREFIX:PATH=${FREETYPE_PREFIX}/install
                    -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
                    -DBUILD_SHARED_LIBS=${BUILD_SHARED_LIBS}
    #--Build step-----------------
    BINARY_DIR      ${FREETYPE_PREFIX}/build
    BUILD_COMMAND
                    ${CMAKE_COMMAND} --build <BINARY_DIR> --config ${Configuration}
    #--Install step---------------
    INSTALL_DIR     ${FREETYPE_PREFIX}/install
    INSTALL_COMMAND
                    ${CMAKE_COMMAND} --build <BINARY_DIR> --target install --config ${Configuration}
    )

# Organize lib into solution folder
project_group(FREETYPE "__external")

# Make sure include directory exists
file(MAKE_DIRECTORY ${FREETYPE_PREFIX}/install/include/freetype2/)

# Add library and include directory
add_library(${LIB} STATIC IMPORTED GLOBAL)
set_property(TARGET ${LIB} PROPERTY IMPORTED_LOCATION_DEBUG   ${FREETYPE_PREFIX}/install/lib/${CMAKE_STATIC_LIBRARY_PREFIX}freetyped${CMAKE_STATIC_LIBRARY_SUFFIX})
set_property(TARGET ${LIB} PROPERTY IMPORTED_LOCATION_RELEASE ${FREETYPE_PREFIX}/install/lib/${CMAKE_STATIC_LIBRARY_PREFIX}freetype${CMAKE_STATIC_LIBRARY_SUFFIX})
set_property(TARGET ${LIB} PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${FREETYPE_PREFIX}/install/include/freetype2/)

add_dependencies(${LIB} FREETYPE)

# Clean-up
unset(LIB)
