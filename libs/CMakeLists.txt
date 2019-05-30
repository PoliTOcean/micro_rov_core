cmake_minimum_required(VERSION 3.5)
project(PolitoceanMircoRovCore)

include_directories(../include)

# Add here all libraries' directories
#add_subdirectory(name_of_directory)

add_subdirectory(Brushless)

# Install and export (do not touch this part)
install(
  EXPORT PolitoceanMircoRovCoreTargets
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/PolitoceanMircoRovCore
  NAMESPACE PolitoceanMircoRovCore::
  FILE PolitoceanMircoRovCoreTargets.cmake
  )

include(CMakePackageConfigHelpers)
configure_package_config_file( 
  "Config.cmake.in" 
  "PolitoceanMircoRovCoreConfig.cmake"
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/PolitoceanMircoRovCore
  PATH_VARS
    CMAKE_INSTALL_LIBDIR
  )

write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/PolitoceanMircoRovCoreConfigVersion.cmake
  VERSION 1.0.0
  COMPATIBILITY SameMajorVersion
  )

### Install Config and ConfigVersion files
install(
  FILES "${CMAKE_CURRENT_BINARY_DIR}/PolitoceanMircoRovCoreConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/PolitoceanMircoRovCoreConfigVersion.cmake"
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/PolitoceanMircoRovCore"
  )
