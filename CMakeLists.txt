cmake_minimum_required(VERSION 3.5)
project(PolitoceanMicroRov)
set(CMAKE_CXX_STANDARD 11)

add_subdirectory(libs)

# Add politocean common libs
add_subdirectory(politocean_common)
include_directories(politocean_common/include)
include_directories(include)
find_package(OpenCV REQUIRED)

# Add executable
add_executable(MicroRovCore main.cpp)

target_link_libraries(MicroRovCore 
                        # Add link libraries
                        -lpaho-mqttpp3                 #mqtt library 
                        PolitoceanCommon::Publisher    #publisher library
                        PolitoceanCommon::Subscriber   #Subscriber library
                        PolitoceanMicroRov::PwmMotor   #PwmMotor library
                        PolitoceanMicroRov::Controller #Controller library
                        ${OpenCV_LIBS}                 #opencv libraries
)
