cmake_minimum_required(VERSION 3.16)
project(opencv-example)

find_package(OpenCV REQUIRED)

SET (CMAKE_BUILD_TYPE "Release")
#SET (CMAKE_BUILD_TYPE "Debug")

SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++17 -pthread")
SET (CMAKE_CXX_FLAGS_RELEASE "-O3")
SET (CMAKE_CXX_FLAGS_DEBUG "-g3 -fsanitize=address")

SET (BASE_DIR ${CMAKE_SOURCE_DIR} )
SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BASE_DIR}/../opencv-example-bin)

add_executable (cp_image cp_image.cpp)
target_link_libraries (cp_image ${OpenCV_LIBS})

add_executable (cp_effects cp_effects.cpp)
target_link_libraries (cp_effects ${OpenCV_LIBS})

add_executable (wav_cmp wav_cmp.cpp)
target_link_libraries (wav_cmp sndfile)

add_executable (test_Golomb test_Golomb.cpp)
target_link_libraries (test_Golomb ${OpenCV_LIBS})

add_executable (codificador_Golomb codificador_Golomb.cpp)
target_link_libraries (codificador_Golomb sndfile)

add_executable (descoficador_Golomb descoficador_Golomb.cpp)
target_link_libraries (descoficador_Golomb sndfile)

add_executable (descoficador_Golomb_imagem descoficador_Golomb_imagem.cpp)
target_link_libraries (descoficador_Golomb_imagem ${OpenCV_LIBS})

add_executable (codificador_Golomb_imagem codificador_Golomb_imagem.cpp)
target_link_libraries (codificador_Golomb_imagem ${OpenCV_LIBS})



