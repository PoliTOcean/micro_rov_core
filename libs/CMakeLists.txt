cmake_minimum_required(VERSION 3.5)
project(PolitoceanMicroRov)

include_directories(../include)

# Add here all libraries' directories
#add_subdirectory(name_of_directory)

add_subdirectory(Brushless)


# Install and export (do not touch this part)
install(
  EXPORT PolitoceanMicroRovTargets
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/PolitoceanMicroRov
  NAMESPACE PolitoceanMicroRov::
  FILE PolitoceanMicroRovTargets.cmake
  )

include(CMakePackageConfigHelpers)
configure_package_config_file( 
  "Config.cmake.in" 
  "PolitoceanMicroRovConfig.cmake"
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/PolitoceanMicroRov
  PATH_VARS
    CMAKE_INSTALL_LIBDIR
  )

write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/PolitoceanMicroRovConfigVersion.cmake
  VERSION 1.0.0
  COMPATIBILITY SameMajorVersion
  )

### Install Config and ConfigVersion files
install(
  FILES "${CMAKE_CURRENT_BINARY_DIR}/PolitoceanMicroRovConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/PolitoceanMicroRovConfigVersion.cmake"
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/PolitoceanMicroRov"
  )
