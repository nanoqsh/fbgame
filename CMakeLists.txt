cmake_minimum_required(VERSION 3.15)
project(fbgame)

set(CMAKE_CXX_STANDARD 17)


set(engine_dir ${CMAKE_CURRENT_SOURCE_DIR}/src/engine)
file(GLOB engine
        ${engine_dir}/*.cpp
        ${engine_dir}/*.h
        )


add_executable(fbgame
        ${engine}
        src/main.cpp
        src/game_config.cpp
        src/game_config.h
        src/game.cpp
        src/game.h
        src/path.h
        )


# Add include and lib directory
target_include_directories(fbgame PUBLIC D:/include)
target_link_directories(fbgame PUBLIC D:/lib)


# Link libs
target_link_libraries(fbgame yaml-cpp glew32s.lib glfw3.lib opengl32.lib SOIL)


# Copy all data files to the build directory
file(GLOB_RECURSE data_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/
        ${CMAKE_CURRENT_SOURCE_DIR}/data/*.yaml
        ${CMAKE_CURRENT_SOURCE_DIR}/data/*.png
        ${CMAKE_CURRENT_SOURCE_DIR}/data/*.jpg
        )

foreach (data_file ${data_files})
    configure_file(${data_file} ${CMAKE_BINARY_DIR}/${data_file} COPYONLY)
endforeach (data_file)

configure_file(config.yaml ${CMAKE_BINARY_DIR}/config.yaml COPYONLY)


# Copy shaders to the build directory
file(GLOB_RECURSE shader_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/
        ${CMAKE_CURRENT_SOURCE_DIR}/shaders/*.glsl
        )

foreach (shader_file ${shader_files})
    configure_file(${shader_file} ${CMAKE_BINARY_DIR}/${shader_file} COPYONLY)
endforeach (shader_file)
