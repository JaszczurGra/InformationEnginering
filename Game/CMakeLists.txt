cmake_minimum_required(VERSION 3.25)
project(Game)

set(CMAKE_CXX_STANDARD 17)


include(FetchContent)
set(BUILD_SHARED_LIBS OFF)
FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.5.1
)
FetchContent_MakeAvailable(SFML)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)
add_executable(
        Game
        main.cpp
)
target_link_libraries(
        Game
        sfml-graphics
)
#add_executable(Game main.cpp)
