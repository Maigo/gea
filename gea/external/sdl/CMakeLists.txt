include(ExternalProject)

#################################################
# LIB: SDL                                      #
#################################################
set(LIB ext_sdl)

message(STATUS "Building ${LIB}")

set(SDL2_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/generated")

set(SDL_BUILDING_LIBRARY ON)

ExternalProject_Add(SDL2
    # DEPENDS
    PREFIX          ${SDL2_PREFIX}
    TMP_DIR         ${SDL2_PREFIX}/temp
    STAMP_DIR       ${SDL2_PREFIX}/stamp
    #--Download step--------------
    DOWNLOAD_DIR    ${SDL2_PREFIX}/download
    URL             https://www.libsdl.org/release/SDL2-2.0.6.tar.gz
    URL_MD5         4c2d602766b48b8f1b19a6f903ef5ecf
    #--Update/Patch step----------
    UPDATE_COMMAND  ""
    #--Configure step-------------
    SOURCE_DIR      ${SDL2_PREFIX}/source
    CMAKE_ARGS      -DCMAKE_INSTALL_PREFIX:PATH=${SDL2_PREFIX}/install
                    -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
                    -DBUILD_SHARED_LIBS=${BUILD_SHARED_LIBS}
    #--Build step-----------------
    BINARY_DIR      ${SDL2_PREFIX}/build
    BUILD_COMMAND
                    ${CMAKE_COMMAND} --build <BINARY_DIR> --config ${Configuration}
    #--Install step---------------
    INSTALL_DIR     ${SDL2_PREFIX}/install
    INSTALL_COMMAND
                    ${CMAKE_COMMAND} --build <BINARY_DIR> --target install --config ${Configuration}
)

# Organize lib into solution folder
project_group(SDL2 "__external")

# Make sure include directory exists
file(MAKE_DIRECTORY ${SDL2_PREFIX}/install/include/SDL2/)

# Add library and include directory
add_library(${LIB} SHARED IMPORTED GLOBAL)
set_property(TARGET ${LIB} PROPERTY IMPORTED_LOCATION ${SDL2_PREFIX}/install/bin/${CMAKE_SHARED_LIBRARY_PREFIX}SDL2${CMAKE_SHARED_LIBRARY_SUFFIX})
set_property(TARGET ${LIB} PROPERTY IMPORTED_IMPLIB ${SDL2_PREFIX}/install/lib/${CMAKE_STATIC_LIBRARY_PREFIX}SDL2${CMAKE_STATIC_LIBRARY_SUFFIX})
set_property(TARGET ${LIB} PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${SDL2_PREFIX}/install/include/SDL2/)
set_property(TARGET ${LIB} PROPERTY INTERFACE_LINK_LIBRARIES ${SDL2_PREFIX}/install/lib/${CMAKE_STATIC_LIBRARY_PREFIX}SDL2main${CMAKE_STATIC_LIBRARY_SUFFIX})

add_dependencies(${LIB} SDL2)

# Clean-up
unset(LIB)
