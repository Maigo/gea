configure_file(config.h.in "${CMAKE_CURRENT_BINARY_DIR}/config.h" @ONLY)

set(TARGET_NAME murmur)

set(SRC
  MurmurHash1.cpp
  MurmurHash2.cpp
  MurmurHash3.cpp
)
set(INC
  MurmurHash1.h
  MurmurHash2.h
  MurmurHash3.h
)

list(APPEND BUILD_TARGETS $TARGET_NAME})

add_library(${TARGET_NAME} STATIC ${SRC} ${INC} config.h.in)

set_target_properties(${TARGET_NAME} PROPERTIES
  PUBLIC_HEADER "${INC};${CMAKE_CURRENT_BINARY_DIR}/config.h")

install(TARGETS ${TARGET_NAME}
  # IMPORTANT: Add the murmur library to the "export-set"
  EXPORT ${PROJECT_NAME}Targets
  RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin
  LIBRARY DESTINATION "${INSTALL_LIB_DIR}" COMPONENT shlib
  ARCHIVE DESTINATION "${INSTALL_LIB_DIR}" COMPONENT lib
  PUBLIC_HEADER DESTINATION "${INSTALL_INCLUDE_DIR}/${TARGET_NAME}"
    COMPONENT dev)

unset(TARGET_NAME)