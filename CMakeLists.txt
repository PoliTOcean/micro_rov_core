cmake_minimum_required(VERSION 3.5)
project(MicroRovCore)
set(CMAKE_CXX_STANDARD 11)

add_subdirectory(politocean_common)
include_directories(politocean_common/include)

add_subdirectory(rov_common)
include_directories(rov_common/include)

add_subdirectory(libs)
include_directories(include)

find_package( OpenCV REQUIRED )

add_executable(MicroRovCore src/main.cpp)
add_executable(Client src/client.cpp)
add_executable(Server src/server.cpp)
target_link_libraries(MicroRovCore -lpaho-mqttpp3
    PolitoceanCommon::Publisher
    PolitoceanCommon::Subscriber
    RovCommon::Controller
    PolitoceanMircoRovCore::Brushless
    ${OpenCV_LIBS}
)

target_link_libraries( Client ${OpenCV_LIBS})
target_link_libraries( Server ${OpenCV_LIBS})
