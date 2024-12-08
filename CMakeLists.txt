cmake_minimum_required(VERSION 3.22.1)
include(GenerateExportHeader)
project(AstrocoreDev)

add_executable(astrodev main.cpp 
testscene.cpp)
add_subdirectory(include/Astrocore)

find_package(spdlog CONFIG REQUIRED)
# Libraries need linked here for building, but ALSO need to be linked in any other project using astrocore
target_link_libraries(astrodev astrocore raylib spdlog::spdlog -lGL -lm -lpthread -ldl -lrt -lX11)
