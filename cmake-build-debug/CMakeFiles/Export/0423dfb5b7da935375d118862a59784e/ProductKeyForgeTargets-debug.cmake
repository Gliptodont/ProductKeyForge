#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "ProductKeyForge::ProductKeyForge" for configuration "Debug"
set_property(TARGET ProductKeyForge::ProductKeyForge APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(ProductKeyForge::ProductKeyForge PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/ProductKeyForge.lib"
  )

list(APPEND _cmake_import_check_targets ProductKeyForge::ProductKeyForge )
list(APPEND _cmake_import_check_files_for_ProductKeyForge::ProductKeyForge "${_IMPORT_PREFIX}/lib/ProductKeyForge.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)