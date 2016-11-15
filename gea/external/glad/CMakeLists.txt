include(ExternalProject)

#################################################
# LIB: GLAD                                     #
#################################################
set(LIB ext_glad)

message(STATUS "Building ${LIB}")

set(GLAD_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/generated")

ExternalProject_Add(GLAD
    # DEPENDS
    PREFIX          ${GLAD_PREFIX}
    TMP_DIR         ${GLAD_PREFIX}/temp
    STAMP_DIR       ${GLAD_PREFIX}/stamp
    #--Download step--------------
    DOWNLOAD_DIR    ${GLAD_PREFIX}/download
#   URL             https://github.com/glfw/glfw/releases/download/3.2.1/glfw-3.2.1.zip
#   URL_MD5         824c99eea073bdd6d2fec76b538f79af
    GIT_REPOSITORY  https://github.com/Maigo/glad.git #https://github.com/Dav1dde/glad.git
    GIT_TAG         "cmake-install"
    #--Update/Patch step----------
    UPDATE_COMMAND  ""
    #--Configure step-------------
    SOURCE_DIR      ${GLAD_PREFIX}/source
    CMAKE_ARGS      -DCMAKE_INSTALL_PREFIX:PATH=${GLAD_PREFIX}/install
                    -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
                    -DBUILD_SHARED_LIBS=${BUILD_SHARED_LIBS}
                    -DGLAD_EXPORT=OFF
                    -DGLAD_INSTALL=ON
    #--Build step-----------------
    BINARY_DIR      ${GLAD_PREFIX}/build
    BUILD_COMMAND
                    ${CMAKE_COMMAND} --build <BINARY_DIR> --config ${Configuration}
    #--Install step---------------
    INSTALL_DIR     ${GLAD_PREFIX}/install
    INSTALL_COMMAND
                    ${CMAKE_COMMAND} --build <BINARY_DIR> --target install --config ${Configuration}
)

# Organize lib into solution folder
project_group(GLAD "__external")

# Make sure include directory exists
file(MAKE_DIRECTORY ${GLAD_PREFIX}/install/include/glad/)

# Add library and include directory
add_library(${LIB} STATIC IMPORTED GLOBAL)
set_property(TARGET ${LIB} PROPERTY IMPORTED_LOCATION				${GLAD_PREFIX}/install/lib/${CMAKE_STATIC_LIBRARY_PREFIX}glad${CMAKE_STATIC_LIBRARY_SUFFIX})
set_property(TARGET ${LIB} PROPERTY INTERFACE_INCLUDE_DIRECTORIES	${GLAD_PREFIX}/install/include/)

add_dependencies(${LIB} GLAD)

# Clean-up
unset(LIB)
