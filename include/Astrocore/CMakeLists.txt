cmake_minimum_required(VERSION 3.22.1)
include(GenerateExportHeader)
project(Astrocore)

add_library(astrocore STATIC
src/component/transform.cpp
src/nodes/node.cpp
src/systems/scenetree.cpp
src/systems/game.cpp
src/systems/rendering/renderer.cpp
src/nodes/shapenode.cpp
src/systems/rendering/rendertarget.cpp
src/systems/input/input.cpp
src/systems/resources/resourcemanager.cpp
src/nodes/spritenode.cpp)

find_package(spdlog CONFIG REQUIRED)
# Libraries need linked here for building, but ALSO need to be linked in any other project using astrocore
target_link_libraries(astrocore raylib spdlog::spdlog -lGL -lm -lpthread -ldl -lrt -lX11)
