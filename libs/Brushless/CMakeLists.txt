cmake_minimum_required(VERSION 3.5)
project(Brushless VERSION 1.0.0 LANGUAGES CXX)

add_library(Brushless
        Brushless.cpp)

add_library(PolitoceanMicroRovArmCore::Brushless ALIAS Brushless)

target_include_directories(Brushless
        PUBLIC
            $<INSTALL_INTERFACE:include>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(Brushless mosquittopp PolitoceanMicroRovArmCore::logger)

target_compile_features(Brushless PRIVATE cxx_auto_type)
target_compile_options(Brushless PRIVATE $<$<CXX_COMPILER_ID:GNU>:-Wall>)

include(GNUInstallDirs)
install(TARGETS Brushless
        EXPORT PolitoceanMicroRovArmCoreTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
