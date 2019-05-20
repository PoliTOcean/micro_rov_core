cmake_minimum_required(VERSION 3.5)
project(MicroRovCore)
set(CMAKE_CXX_STANDARD 11)

add_subdirectory(politocean_common)
include_directories(politocean_common/include)

add_subdirectory(rov_common)
include_directories(rov_common/include)


find_package( OpenCV REQUIRED )

add_executable(MicroRovCore main.cpp)
target_link_libraries(MicroRovCore -lpaho-mqttpp3 
    PolitoceanCommon::Publisher    #publisher library
    PolitoceanCommon::Subscriber   #Subscriber library
    RovCommon::Controller #Controller library
    RovCommon::PwmMotor   #PwmMotor library
    ${OpenCV_LIBS}                 #opencv libraries
)
