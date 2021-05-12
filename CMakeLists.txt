CMAKE_MINIMUM_REQUIRED(VERSION 3.13)
project(zhizha CXX)
set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCE_FILES project/src/*.cpp project/src/*.c)
file(GLOB_RECURSE HEADER_FILES project/include/*.h project/include/*.hpp)
file(GLOB_RECURSE RESOURCES project/resources/*.*)

if (UNIX)
	find_package(GLEW REQUIRED)

	set(CMAKE_PREFIX_PATH ${PROJECT_SOURCE_DIR}/Lib/Linux)
	set(CMAKE_LIBRARY_PATH ${PROJECT_SOURCE_DIR}/Lib/Linux)
	set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-pthread -ltbb")
elseif (WIN32)
	set(CMAKE_PREFIX_PATH ${PROJECT_SOURCE_DIR}/Lib/Windows/glew-2.1.0)
	set(CMAKE_LIBRARY_PATH ${PROJECT_SOURCE_DIR}/Lib/Windows/glew-2.1.0/lib/Release/x64)
	find_package(GLEW REQUIRED)

	set(CMAKE_PREFIX_PATH ${PROJECT_SOURCE_DIR}/Lib/Windows)
	set(CMAKE_LIBRARY_PATH ${PROJECT_SOURCE_DIR}/Lib/Windows)
	set(SFML_STATIC_LIBRARIES TRUE)
endif()

add_subdirectory(GameEngine)
include_directories(GameEngine/include)
include_directories(project/include)

add_executable(main ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(main PUBLIC GameEngine)
target_link_libraries(main PRIVATE GLEW::GLEW)

# Move resources to build dir
foreach (res ${RESOURCES})
	configure_file(${res} ${CMAKE_BINARY_DIR} COPYONLY)
endforeach ()
