cmake_minimum_required(VERSION 3.5)
project(PolitoceanMicroRov)
set(CMAKE_CXX_STANDARD 11)

add_subdirectory(libs)
include_directories(politocean_common/include)

add_subdirectory(rov_common)
include_directories(rov_common/include)
include_directories(politocean_common/include)
include_directories(include)
find_package(OpenCV REQUIRED)

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
