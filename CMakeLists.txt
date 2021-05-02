CMAKE_MINIMUM_REQUIRED(VERSION 3.13)
project(zhizha)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(GameEngine)
include_directories(GameEngine/include)

add_executable(main main.cpp)
target_link_libraries(main PUBLIC GameEngine pthread)