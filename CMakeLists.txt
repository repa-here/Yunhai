cmake_minimum_required(VERSION 3.16)
project(YunhaiEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG        2.6.x
)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(SFML)

file(GLOB_RECURSE SOURCES 
    "src/*.cpp"
    "maps/*.hpp"
)

add_executable(${PROJECT_NAME} ${SOURCES}
 "interface/main_ui/MainWindow.cpp"
 "src/player/Player.cpp"
 "src/raycast/Raycaster.cpp"
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/maps
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/player
)

target_link_libraries(${PROJECT_NAME} PRIVATE 
    sfml-graphics 
    sfml-window 
    sfml-system 
    sfml-audio
)