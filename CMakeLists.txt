CMAKE_MINIMUM_REQUIRED(VERSION 3.13)
project(zhizha)
set(CMAKE_CXX_STANDARD 20)

include_directories(GameEngine/include)
add_subdirectory(GameEngine)
add_executable(main main.cpp GameEngine)