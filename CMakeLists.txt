CMAKE_MINIMUM_REQUIRED(VERSION 3.13)
project(zhizha)
set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCE_FILES project/src/*.cpp project/src/*.c)
file(GLOB_RECURSE HEADER_FILES project/include/*.h project/include/*.hpp)
file(GLOB_RECURSE RESOURCES project/resources/*)

if (UNIX)
	set(CMAKE_PREFIX_PATH ${PROJECT_SOURCE_DIR}/Lib/Linux)
	set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-pthread -ltbb -ldl")
elseif (WIN32)
	set(CMAKE_PREFIX_PATH ${PROJECT_SOURCE_DIR}/Lib/Windows)
	set(SFML_STATIC_LIBRARIES TRUE)
endif()

add_subdirectory(ECS)
add_subdirectory(glad)
include_directories(glad/include)
include_directories(ECS/include)
include_directories(project/include)

add_executable(main ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(main PUBLIC ECS)
target_link_libraries(main PUBLIC glad)

# Move resources to build dir
foreach (item ${RESOURCES})
	configure_file(${item} ${CMAKE_CURRENT_BINARY_DIR}/ COPYONLY)
endforeach ()