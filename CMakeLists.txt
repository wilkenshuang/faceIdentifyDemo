cmake_minimum_required(VERSION 2.6)
project(mtcnn_c)

set(OpenCV_DIR "/app/opencv-3.3.0")
SET(CMAKE_C_COMPILER g++)
SET(CMAK_CXX_COMPILER g++)
add_compile_options(-std=c++11)
add_compile_options(-m64)

include_directories(
    ${mtcnn_c_SOURCE_DIR}/include/ 
    /usr/local/cuda/include)
link_directories(
    ${mtcnn_c_SOURCE_DIR}/lib/
    /usr/local/cuda/lib64)

add_executable(mtcnn_c main.cpp get_token.cpp base64.cpp)
find_package( OpenCV REQUIRED)
target_link_libraries(mtcnn_c 
    -lcaffe 
    -lboost_system 
    -lcurl
    -ljson
    -lboost_filesystem
    -lopencv_core 
    -lopencv_highgui 
    -lopencv_imgproc
    -lopencv_imgcodecs
    ${OpenCV_LIBS}    
    -lglog
    -lgflags
    -lprotobuf
    -lm
    -lhdf5
    -lhdf5_hl
)

#install(TARGETS mtcnn_c RUNTIME DESTINATION bin)
