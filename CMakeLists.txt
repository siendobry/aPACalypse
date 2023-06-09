cmake_minimum_required(VERSION 3.25)
project(apacalypse)

set(CMAKE_CXX_STANDARD 20)

set(SDL2_PATH "E:\\libs\\SDL")
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/)
list(APPEND CMAKE_PREFIX_PATH "E:\\libs\\SDL\\libs\\cmake")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)

include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR} ${SDL2_MIXER_INCLUDE_DIR})

add_executable(${PROJECT_NAME} main.cpp include/defs.hpp include/entity.hpp include/vector.hpp include/gameloop.hpp src/entity.cpp src/vector.cpp src/gameloop.cpp include/app.hpp src/app.cpp include/player.hpp src/player.cpp include/bullet.hpp src/bullet.cpp src/enemy.cpp include/enemy.hpp)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES} ${SDL2_MIXER_LIBRARIES})