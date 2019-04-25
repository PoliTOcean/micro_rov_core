cmake_minimum_required(VERSION 3.5)
project(PolitoceanMicroRov)
set(CMAKE_CXX_STANDARD 11)

# Add politocean common libs
add_subdirectory(politocean_common)
include_directories(politocean_common/include)

find_package( OpenCV REQUIRED )

# Add executable
add_executable(MicroRovCore main.cpp)
target_link_libraries(MicroRovCore 
                        # Add link libraries
                        -lpaho-mqttpp3 #mqtt library 
                        PolitoceanCommon::Publisher #publisher library
                        #opencv libraries
                        -I/usr/include/opencv 
                        -lopencv_shape 
                        -lopencv_stitching 
                        -lopencv_superres 
                        -lopencv_videostab 
                        -lopencv_aruco 
                        -lopencv_bgsegm 
                        -lopencv_bioinspired 
                        -lopencv_ccalib 
                        -lopencv_datasets 
                        -lopencv_dpm 
                        -lopencv_face 
                        -lopencv_freetype 
                        -lopencv_fuzzy 
                        -lopencv_hdf 
                        -lopencv_line_descriptor 
                        -lopencv_optflow 
                        -lopencv_video 
                        -lopencv_plot 
                        -lopencv_reg 
                        -lopencv_saliency 
                        -lopencv_stereo 
                        -lopencv_structured_light 
                        -lopencv_phase_unwrapping 
                        -lopencv_rgbd 
                        -lopencv_viz 
                        -lopencv_surface_matching 
                        -lopencv_text 
                        -lopencv_ximgproc 
                        -lopencv_calib3d 
                        -lopencv_features2d 
                        -lopencv_flann 
                        -lopencv_xobjdetect 
                        -lopencv_objdetect 
                        -lopencv_ml 
                        -lopencv_xphoto 
                        -lopencv_highgui 
                        -lopencv_videoio 
                        -lopencv_imgcodecs 
                        -lopencv_photo 
                        -lopencv_imgproc 
                        -lopencv_core )