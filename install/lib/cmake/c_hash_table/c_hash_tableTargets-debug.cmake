#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "c_hash_table::c_hash_table" for configuration "Debug"
set_property(TARGET c_hash_table::c_hash_table APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(c_hash_table::c_hash_table PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "C"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libc_hash_table.a"
  )

list(APPEND _cmake_import_check_targets c_hash_table::c_hash_table )
list(APPEND _cmake_import_check_files_for_c_hash_table::c_hash_table "${_IMPORT_PREFIX}/lib/libc_hash_table.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
