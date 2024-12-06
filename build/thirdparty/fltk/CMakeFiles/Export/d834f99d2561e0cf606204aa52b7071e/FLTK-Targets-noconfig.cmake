#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "fltk::fltk" for configuration ""
set_property(TARGET fltk::fltk APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(fltk::fltk PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "C;CXX"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libfltk.a"
  )

list(APPEND _cmake_import_check_targets fltk::fltk )
list(APPEND _cmake_import_check_files_for_fltk::fltk "${_IMPORT_PREFIX}/lib/libfltk.a" )

# Import target "fltk::forms" for configuration ""
set_property(TARGET fltk::forms APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(fltk::forms PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "CXX"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libfltk_forms.a"
  )

list(APPEND _cmake_import_check_targets fltk::forms )
list(APPEND _cmake_import_check_files_for_fltk::forms "${_IMPORT_PREFIX}/lib/libfltk_forms.a" )

# Import target "fltk::images" for configuration ""
set_property(TARGET fltk::images APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(fltk::images PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "CXX"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libfltk_images.a"
  )

list(APPEND _cmake_import_check_targets fltk::images )
list(APPEND _cmake_import_check_files_for_fltk::images "${_IMPORT_PREFIX}/lib/libfltk_images.a" )

# Import target "fltk::gl" for configuration ""
set_property(TARGET fltk::gl APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(fltk::gl PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "CXX"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libfltk_gl.a"
  )

list(APPEND _cmake_import_check_targets fltk::gl )
list(APPEND _cmake_import_check_files_for_fltk::gl "${_IMPORT_PREFIX}/lib/libfltk_gl.a" )

# Import target "fltk::fltk-shared" for configuration ""
set_property(TARGET fltk::fltk-shared APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(fltk::fltk-shared PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libfltk.so.1.4.0"
  IMPORTED_SONAME_NOCONFIG "libfltk.so.1.4"
  )

list(APPEND _cmake_import_check_targets fltk::fltk-shared )
list(APPEND _cmake_import_check_files_for_fltk::fltk-shared "${_IMPORT_PREFIX}/lib/libfltk.so.1.4.0" )

# Import target "fltk::forms-shared" for configuration ""
set_property(TARGET fltk::forms-shared APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(fltk::forms-shared PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libfltk_forms.so.1.4.0"
  IMPORTED_SONAME_NOCONFIG "libfltk_forms.so.1.4"
  )

list(APPEND _cmake_import_check_targets fltk::forms-shared )
list(APPEND _cmake_import_check_files_for_fltk::forms-shared "${_IMPORT_PREFIX}/lib/libfltk_forms.so.1.4.0" )

# Import target "fltk::images-shared" for configuration ""
set_property(TARGET fltk::images-shared APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(fltk::images-shared PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libfltk_images.so.1.4.0"
  IMPORTED_SONAME_NOCONFIG "libfltk_images.so.1.4"
  )

list(APPEND _cmake_import_check_targets fltk::images-shared )
list(APPEND _cmake_import_check_files_for_fltk::images-shared "${_IMPORT_PREFIX}/lib/libfltk_images.so.1.4.0" )

# Import target "fltk::gl-shared" for configuration ""
set_property(TARGET fltk::gl-shared APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(fltk::gl-shared PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libfltk_gl.so.1.4.0"
  IMPORTED_SONAME_NOCONFIG "libfltk_gl.so.1.4"
  )

list(APPEND _cmake_import_check_targets fltk::gl-shared )
list(APPEND _cmake_import_check_files_for_fltk::gl-shared "${_IMPORT_PREFIX}/lib/libfltk_gl.so.1.4.0" )

# Import target "fltk::options" for configuration ""
set_property(TARGET fltk::options APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(fltk::options PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/bin/fltk-options"
  )

list(APPEND _cmake_import_check_targets fltk::options )
list(APPEND _cmake_import_check_files_for_fltk::options "${_IMPORT_PREFIX}/bin/fltk-options" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
