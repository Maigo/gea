###############################################################################
# CMakeMacroParseArguments                                                    #
###############################################################################
MACRO(PARSE_ARGUMENTS prefix arg_names option_names)
  SET(DEFAULT_ARGS)
  FOREACH(arg_name ${arg_names})    
    SET(${prefix}_${arg_name})
  ENDFOREACH(arg_name)
  FOREACH(option ${option_names})
    SET(${prefix}_${option} FALSE)
  ENDFOREACH(option)

  SET(current_arg_name DEFAULT_ARGS)
  SET(current_arg_list)
  FOREACH(arg ${ARGN})            
    SET(larg_names ${arg_names})    
    LIST(FIND larg_names "${arg}" is_arg_name)                   
    IF (is_arg_name GREATER -1)
      SET(${prefix}_${current_arg_name} ${current_arg_list})
      SET(current_arg_name ${arg})
      SET(current_arg_list)
    ELSE (is_arg_name GREATER -1)
      SET(loption_names ${option_names})    
      LIST(FIND loption_names "${arg}" is_option)            
      IF (is_option GREATER -1)
        SET(${prefix}_${arg} TRUE)
      ELSE (is_option GREATER -1)
        SET(current_arg_list ${current_arg_list} ${arg})
      ENDIF (is_option GREATER -1)
    ENDIF (is_arg_name GREATER -1)
  ENDFOREACH(arg)
  SET(${prefix}_${current_arg_name} ${current_arg_list})
ENDMACRO(PARSE_ARGUMENTS)

###############################################################################
# CMakeMacroListOperations                                                    #
###############################################################################
MACRO(LIST_CAR var)
  SET(${var} ${ARGV1})
ENDMACRO(LIST_CAR)

MACRO(LIST_CDR var junk)
  SET(${var} ${ARGN})
ENDMACRO(LIST_CDR)

MACRO(LIST_LENGTH var)
  SET(entries)
  FOREACH(e ${ARGN})
    SET(entries "${entries}.")
  ENDFOREACH(e)
  STRING(LENGTH ${entries} ${var})
ENDMACRO(LIST_LENGTH)

MACRO(LIST_INDEX var index)
  SET(list . ${ARGN})
  FOREACH(i RANGE 1 ${index})
    LIST_CDR(list ${list})
  ENDFOREACH(i)
  LIST_CAR(${var} ${list})
ENDMACRO(LIST_INDEX)

MACRO(LIST_CONTAINS var value)
  SET(${var})
  FOREACH (value2 ${ARGN})
    IF (${value} STREQUAL ${value2})
      SET(${var} TRUE)
    ENDIF (${value} STREQUAL ${value2})
  ENDFOREACH (value2)
ENDMACRO(LIST_CONTAINS)

# LIST_FILTER(<list> <regexp_var> [<regexp_var> ...]
#             [OUTPUT_VARIABLE <variable>])
# Removes items from <list> which do not match any of the specified
# regular expressions. An optional argument OUTPUT_VARIABLE
# specifies a variable in which to store the matched items instead of
# updating <list>
# As regular expressions can not be given to macros (see bug #5389), we pass
# variable names whose content is the regular expressions.
# Note that this macro requires PARSE_ARGUMENTS macro, available here:
# http://www.cmake.org/Wiki/CMakeMacroParseArguments
MACRO(LIST_FILTER)
  PARSE_ARGUMENTS(LIST_FILTER "OUTPUT_VARIABLE" "" ${ARGV})
  # Check arguments.
  LIST(LENGTH LIST_FILTER_DEFAULT_ARGS LIST_FILTER_default_length)
  IF (${LIST_FILTER_default_length} EQUAL 0)
    MESSAGE(FATAL_ERROR "LIST_FILTER: missing list variable.")
  ENDIF (${LIST_FILTER_default_length} EQUAL 0)
  IF (${LIST_FILTER_default_length} EQUAL 1)
    MESSAGE(FATAL_ERROR "LIST_FILTER: missing regular expression variable.")
  ENDIF (${LIST_FILTER_default_length} EQUAL 1)
  # Reset output variable
  IF (NOT LIST_FILTER_OUTPUT_VARIABLE)
    SET(LIST_FILTER_OUTPUT_VARIABLE "LIST_FILTER_internal_output")
  ENDIF (NOT LIST_FILTER_OUTPUT_VARIABLE)
  SET(${LIST_FILTER_OUTPUT_VARIABLE})
  # Extract input list from arguments
  LIST(GET LIST_FILTER_DEFAULT_ARGS 0 LIST_FILTER_input_list)
  LIST(REMOVE_AT LIST_FILTER_DEFAULT_ARGS 0)
  FOREACH(LIST_FILTER_item ${${LIST_FILTER_input_list}})
    FOREACH(LIST_FILTER_regexp_var ${LIST_FILTER_DEFAULT_ARGS})
      FOREACH(LIST_FILTER_regexp ${${LIST_FILTER_regexp_var}})
        IF (${LIST_FILTER_item} MATCHES ${LIST_FILTER_regexp})
          LIST(APPEND ${LIST_FILTER_OUTPUT_VARIABLE} ${LIST_FILTER_item})
        ENDIF (${LIST_FILTER_item} MATCHES ${LIST_FILTER_regexp})
      ENDFOREACH(LIST_FILTER_regexp ${${LIST_FILTER_regexp_var}})
    ENDFOREACH(LIST_FILTER_regexp_var)
  ENDFOREACH(LIST_FILTER_item)
  # If OUTPUT_VARIABLE is not specified, overwrite the input list.
  IF (${LIST_FILTER_OUTPUT_VARIABLE} STREQUAL "LIST_FILTER_internal_output")
    SET(${LIST_FILTER_input_list} ${${LIST_FILTER_OUTPUT_VARIABLE}})
  ENDIF (${LIST_FILTER_OUTPUT_VARIABLE} STREQUAL "LIST_FILTER_internal_output")
ENDMACRO(LIST_FILTER)

###############################################################################
# CMakeCustomMacros                                                           #
###############################################################################
MACRO(FIND_PACKAGE_CHECK)
  PARSE_ARGUMENTS(FIND_PACKAGE_CHECK "COMPONENTS" "REQUIRED" ${ARGV})
  # Check arguments.
  LIST(LENGTH FIND_PACKAGE_CHECK_DEFAULT_ARGS FIND_PACKAGE_CHECK_default_length)
  IF (${FIND_PACKAGE_CHECK_default_length} EQUAL 0)
    MESSAGE(FATAL_ERROR "FIND_PACKAGE_CHECK: missing package name.")
  ENDIF (${FIND_PACKAGE_CHECK_default_length} EQUAL 0)
  # Extract package name from arguments
  LIST(GET FIND_PACKAGE_CHECK_DEFAULT_ARGS 0 FIND_PACKAGE_CHECK_package_name)
  # Echo find_package results
  IF (${FIND_PACKAGE_CHECK_package_name}_FOUND)
    MESSAGE(STATUS "Including package ${FIND_PACKAGE_CHECK_package_name}... OK")
    INCLUDE_DIRECTORIES(${${FIND_PACKAGE_CHECK_package_name}_INCLUDE_DIR})
  ELSEIF (ARG_REQUIRED)
    MESSAGE(FATAL_ERROR "Including package ${FIND_PACKAGE_CHECK_package_name}... FAIL")
  ELSE ()
    MESSAGE(WARNING "Including package ${FIND_PACKAGE_CHECK_package_name}... FAIL")
  ENDIF ()
ENDMACRO(FIND_PACKAGE_CHECK)

MACRO(PROJECT_GROUP TARGET_NAME FOLDER_PATH)
    # Organize projects into folders    
    SET_PROPERTY(TARGET ${TARGET_NAME} PROPERTY FOLDER ${FOLDER_PATH})
ENDMACRO(PROJECT_GROUP)

MACRO(FORCE_INCLUDE_HEADER HEADER_FILE)
  IF (MSVC)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /FI\"${HEADER_FILE}\"")
  ELSE (MSVC)
    MESSAGE(FETAL ERROR "force_include: unsupported compiler")
  endif (MSVC)
ENDMACRO(FORCE_INCLUDE_HEADER)
