CMAKE_MINIMUM_REQUIRED(VERSION 3.13)
project(zhizha CXX)
set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCE_FILES project/src/*.cpp)

if (UNIX)
	set(CMAKE_PREFIX_PATH ${PROJECT_SOURCE_DIR}/Lib/Linux)
elseif (WIN32)
	set(CMAKE_PREFIX_PATH ${PROJECT_SOURCE_DIR}/Lib/Windows)
	set(SFML_STATIC_LIBRARIES TRUE)
endif()

add_subdirectory(GameEngine)
include_directories(GameEngine/include)
include_directories(project/include)

add_executable(main ${SOURCE_FILES})
target_link_libraries(main PUBLIC GameEngine)
