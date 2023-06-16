cmake_minimum_required(VERSION 3.25)
project(apacalypse)

set(CMAKE_CXX_STANDARD 20)

#set(SDL2_PATH "E:\\libs\\SDL")
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

#find_package(SDL2 REQUIRED)
#find_package(SDL2_image REQUIRED)
#find_package(SDL2_ttf REQUIRED)

INCLUDE(FindPkgConfig)

pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_IMG REQUIRED SDL2_image)
pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)

#include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR})

include_directories(${SDL2_INCLUDE_DIRS}
        ${SDL2_IMG_INCLUDE_DIRS}
        ${SDL2_TTF_INCLUDE_DIRS})

link_directories (${SDL2_LIBRARY_DIRS}
        ${SDL2_IMG_LIBRARY_DIRS}
        ${SDL2_TTF_LIBRARY_DIRS})

add_executable(${PROJECT_NAME} main.cpp include/defs.hpp include/entity.hpp include/vector.hpp include/gameloop.hpp src/entity.cpp src/vector.cpp src/gameloop.cpp include/app.hpp src/app.cpp include/player.hpp src/player.cpp include/bullet.hpp src/bullet.cpp src/enemy.cpp include/enemy.hpp include/button.hpp include/text.hpp src/text.cpp)

#target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${SDL2_TTF_LIBRARY} -lmingw32 -lSDL2main -lSDL2 -lSDL2image -SDL2ttf -mwindows)

target_link_libraries (apacalypse
        ${SDL2_LIBRARIES}
        ${SDL2_IMG_LIBRARIES}
        ${SDL2_TTF_LIBRARIES})