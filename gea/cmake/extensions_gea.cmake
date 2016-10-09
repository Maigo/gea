# --------------------------------------------------------------------------- #
# source_group_ext                                                            #
# --------------------------------------------------------------------------- #
function(SOURCE_GROUP_EXT)
    set(arg_flags     )                 # 0-length arguments (eg. FAST, OPTIONAL)
    set(arg_tuples    PREFIX)           # 1-length arguments (eg. TARGET <target>, NAME <name>)
    set(arg_lists     FILES UNPREFIX)   # n-length arguments (eg. FILES <file-list>, CONFIGURATION <configuration-list>)
    cmake_parse_arguments(SOURCE_GROUP_EXT "${arg_flags}" "${arg_tuples}" "${arg_lists}" ${ARGN})

    foreach(var_file ${SOURCE_GROUP_EXT_FILES}) 
        get_filename_component(var_group "${var_file}" PATH)

        # strip UNPREFIX (optional)
        foreach (unprefix ${SOURCE_GROUP_EXT_UNPREFIX})
            string(REGEX REPLACE "(\\./)?(${unprefix})/?" "" var_group "${var_group}")
        endforeach(unprefix)
        # ... and changes /'s to \\'s
        string(REPLACE "/" "\\" var_group "${var_group}")
        
        # prepend PREFIX (optional)
        if (NOT "${SOURCE_GROUP_EXT_PREFIX}" STREQUAL "")
          set(var_group "${SOURCE_GROUP_EXT_PREFIX}\\${var_group}")
        endif()

        # set source_group for file
        source_group("${var_group}" FILES "${var_file}")
    endforeach(var_file)
endfunction(SOURCE_GROUP_EXT)