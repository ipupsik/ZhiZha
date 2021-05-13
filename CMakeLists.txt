CMAKE_MINIMUM_REQUIRED(VERSION 3.13)
project(zhizha)
set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCE_FILES project/src/*.cpp project/src/*.c)
file(GLOB_RECURSE HEADER_FILES project/include/*.h project/include/*.hpp)
file(GLOB_RECURSE RESOURCES project/resources/*)

if (UNIX)
	set(CMAKE_PREFIX_PATH ${PROJECT_SOURCE_DIR}/Lib/Linux)
elseif (WIN32)
	set(CMAKE_PREFIX_PATH ${PROJECT_SOURCE_DIR}/Lib/Windows)
	set(SFML_STATIC_LIBRARIES TRUE)
endif()

find_package(Threads REQUIRED)

add_subdirectory(ECS)
add_subdirectory(glad)
include_directories(glad/include)
include_directories(ECS/include)
include_directories(project/include)

add_executable(main ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(main PRIVATE ECS)
target_link_libraries(main PRIVATE glad)
target_link_libraries(main PRIVATE ${CMAKE_DL_LIBS})

install(FILES ${RESOURCES}
		TYPE DATA)
install(TARGETS main
		TYPE RUNTIME)

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/share/)
foreach(item IN LISTS RESOURCES)
	configure_file(${item} ${CMAKE_BINARY_DIR}/share/ COPYONLY)
endforeach()

set(WORKING_DIRECTORY $<IF:BUILD_INTERFACE,${CMAKE_BINARY_DIR},<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}>/share/)