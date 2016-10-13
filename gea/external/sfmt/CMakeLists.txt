include(ExternalProject)

#################################################
# LIB: SFMT                                     #
#################################################
set(LIB ext_sfmt)

message(STATUS "Building ${LIB}")

set(PATCH_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/patch")
set(SFMT_PREFIX  "${CMAKE_CURRENT_SOURCE_DIR}/generated")

ExternalProject_Add(SFMT
    # DEPENDS
    PREFIX          ${SFMT_PREFIX}
    TMP_DIR         ${SFMT_PREFIX}/temp
    STAMP_DIR       ${SFMT_PREFIX}/stamp
    #--Download step--------------
    DOWNLOAD_DIR    ${SFMT_PREFIX}/download
    URL             http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/SFMT/SFMT-src-1.4.1.zip
    URL_MD5         e667a96e686900da44023d6cb45a1779
    #--Update/Patch step----------
    UPDATE_COMMAND  ""
    PATCH_COMMAND   ${CMAKE_COMMAND} -E copy_directory ${PATCH_PREFIX}/ ${SFMT_PREFIX}/source/
    #--Configure step-------------
    SOURCE_DIR      ${SFMT_PREFIX}/source
    CMAKE_ARGS      -DCMAKE_INSTALL_PREFIX:PATH=${SFMT_PREFIX}/install
                    -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
                    -DBUILD_SHARED_LIBS=${BUILD_SHARED_LIBS}
    #--Build step-----------------
    BINARY_DIR      ${SFMT_PREFIX}/build
    BUILD_COMMAND
                    ${CMAKE_COMMAND} --build <BINARY_DIR> --config ${Configuration}
    #--Install step---------------
    INSTALL_DIR     ${SFMT_PREFIX}/install
    INSTALL_COMMAND
                    ${CMAKE_COMMAND} --build <BINARY_DIR> --target install --config ${Configuration}
)

# Organize lib into solution folder
project_group(SFMT "__external")

# Make sure include directory exists
file(MAKE_DIRECTORY ${SFMT_PREFIX}/install/include/)

# Add library and include directory
add_library(${LIB} STATIC IMPORTED GLOBAL)
set_property(TARGET ${LIB} PROPERTY IMPORTED_LOCATION ${SFMT_PREFIX}/install/lib/${CMAKE_STATIC_LIBRARY_PREFIX}SFMT${CMAKE_STATIC_LIBRARY_SUFFIX})
set_property(TARGET ${LIB} PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${SFMT_PREFIX}/install/include/)

add_dependencies(${LIB} SFMT)

# Clean-up
unset(LIB)
