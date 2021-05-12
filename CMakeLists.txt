CMAKE_MINIMUM_REQUIRED(VERSION 3.13)
project(zhizha CXX)
set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCE_FILES project/src/*.cpp)
file(GLOB_RECURSE HEADER_FILES project/include/*.h)

if (UNIX)
	set(CMAKE_PREFIX_PATH ${PROJECT_SOURCE_DIR}/Lib/Linux)
	set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-pthread -ltbb")
elseif (WIN32)
	set(CMAKE_PREFIX_PATH ${PROJECT_SOURCE_DIR}/Lib/Windows)
	set(SFML_STATIC_LIBRARIES TRUE)
endif()

find_package(OpenGL REQUIRED)

add_subdirectory(GameEngine)
include_directories(GameEngine/include)
include_directories(Lib/Windows/glad/include)
include_directories(project/include)

add_executable(main ${SOURCE_FILES} ${HEADER_FILES} Lib/Windows/glad/src/glad.c)
target_link_libraries(main PUBLIC GameEngine opengl32 glad)
