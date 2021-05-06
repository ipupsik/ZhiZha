CMAKE_MINIMUM_REQUIRED(VERSION 3.13)
project(zhizha CXX)
set(CMAKE_CXX_STANDARD 20)

if (UNIX)
	set(CMAKE_PREFIX_PATH ${PROJECT_SOURCE_DIR}/Lib/Linux)
elseif (WIN32)
	set(CMAKE_PREFIX_PATH ${PROJECT_SOURCE_DIR}/Lib/Windows)
	set(SFML_STATIC_LIBRARIES TRUE)
endif()

add_subdirectory(GameEngine)
include_directories(GameEngine/include)

add_executable(main main.cpp)
target_link_libraries(main PUBLIC GameEngine)
