cmake_minimum_required(VERSION 3.5)
project(MicroRovCore)
set(CMAKE_CXX_STANDARD 11)

if(" ${CMAKE_SOURCE_DIR}" STREQUAL " ${CMAKE_BINARY_DIR}")
  message(FATAL_ERROR "
	In-source builds are not allowed.
	Please, create a separate directory for build files (e.g. build/).
	Delete CMakeCache.txt, make a separate dir and try again.
	")
endif()

add_subdirectory(politocean_common)
include_directories(politocean_common/include)

add_subdirectory(rov_common)
include_directories(rov_common/include)

add_subdirectory(libs)

find_package( OpenCV REQUIRED )

add_executable(MicroRovCore src/main.cpp)
target_link_libraries(MicroRovCore -lpaho-mqttpp3 
    PolitoceanCommon::Publisher
    PolitoceanCommon::Subscriber
    RovCommon::Controller
    PolitoceanMircoRovCore::Brushless
    ${OpenCV_LIBS}
)
