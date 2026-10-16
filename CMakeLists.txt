
cmake_minimum_required(VERSION 3.16)

project(c_hash_table
    VERSION 0.1.0
    LANGUAGES C
)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# Build a static library.
add_library(c_hash_table STATIC
    src/entry.c
    src/hashtable.c
)

# Convenient target name for other projects.
add_library(c_hash_table::c_hash_table ALIAS c_hash_table)

# Require C11.
target_compile_features(c_hash_table PUBLIC c_std_11)

# Expose public headers while building and after installation.
target_include_directories(c_hash_table PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# Install the compiled library.
install(TARGETS c_hash_table
    EXPORT c_hash_tableTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Install public headers.
install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Export the target for use by other CMake projects.
install(EXPORT c_hash_tableTargets
    FILE c_hash_tableTargets.cmake
    NAMESPACE c_hash_table::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/c_hash_table
)

# Generate package configuration and version files.
configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/c_hash_tableConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/c_hash_tableConfig.cmake"
    INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/c_hash_table"
)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/c_hash_tableConfigVersion.cmake"
    VERSION "${PROJECT_VERSION}"
    COMPATIBILITY SameMajorVersion
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/c_hash_tableConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/c_hash_tableConfigVersion.cmake"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/c_hash_table"
)

# file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")

# add_executable("${CMAKE_PROJECT_NAME}")

# target_include_directories("${CMAKE_PROJECT_NAME}" PRIVATE "${PROJECT_SOURCE_DIR}/include")

# target_sources("${CMAKE_PROJECT_NAME}" PRIVATE ${SRC_FILES})

