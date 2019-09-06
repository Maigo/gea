include(ExternalProject)

#################################################
# LIB: MURMUR                                   #
#################################################
set(LIB ext_murmur)

message(STATUS "Building ${LIB}")

set(PATCH_PREFIX  "${CMAKE_CURRENT_SOURCE_DIR}/patch")
set(MURMUR_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/generated")

ExternalProject_Add(MURMUR
    # DEPENDS
    PREFIX          ${MURMUR_PREFIX}
    TMP_DIR         ${MURMUR_PREFIX}/temp
    STAMP_DIR       ${MURMUR_PREFIX}/stamp
    #--Download step--------------
    DOWNLOAD_DIR    ${MURMUR_PREFIX}/download
#   URL             https://github.com/aappleby/smhasher/archive/master.zip
#   URL_MD5         dc40ac11707fb253ee8aaa9a5023eeba
    GIT_REPOSITORY  https://github.com/aappleby/smhasher.git
    GIT_TAG         61a0530f28277f2e850bfc39600ce61d02b518de
    #--Update/Patch step----------
    UPDATE_COMMAND  ""
    PATCH_COMMAND   ${CMAKE_COMMAND} -E copy_directory ${PATCH_PREFIX}/ ${MURMUR_PREFIX}/source/
    #--Configure step-------------
    SOURCE_DIR      ${MURMUR_PREFIX}/source
    CMAKE_ARGS      -DCMAKE_INSTALL_PREFIX:PATH=${MURMUR_PREFIX}/install
                    -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
                    -DBUILD_SHARED_LIBS=${BUILD_SHARED_LIBS}
    #--Build step-----------------
    BINARY_DIR      ${MURMUR_PREFIX}/build
    BUILD_COMMAND
                    ${CMAKE_COMMAND} --build <BINARY_DIR> --config ${CMAKE_CFG_INTDIR}
    #--Install step---------------
    INSTALL_DIR     ${MURMUR_PREFIX}/install
    INSTALL_COMMAND
                    ${CMAKE_COMMAND} --build <BINARY_DIR> --target install --config ${CMAKE_CFG_INTDIR}
)

# Organize lib into solution folder
project_group(MURMUR "__external")

# Make sure include directory exists
file(MAKE_DIRECTORY ${MURMUR_PREFIX}/install/include/)

# Add library and include directory
add_library(${LIB} STATIC IMPORTED GLOBAL)
set_property(TARGET ${LIB} PROPERTY IMPORTED_LOCATION ${MURMUR_PREFIX}/install/lib/${CMAKE_STATIC_LIBRARY_PREFIX}MURMUR${CMAKE_STATIC_LIBRARY_SUFFIX})
set_property(TARGET ${LIB} PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${MURMUR_PREFIX}/install/include/)

add_dependencies(${LIB} MURMUR)

# Clean-up
unset(LIB)
