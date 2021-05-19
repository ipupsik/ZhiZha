CMAKE_MINIMUM_REQUIRED(VERSION 3.19)
project(zhizha C CXX)
set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCE_FILES project/src/*.cpp project/src/*.c)
file(GLOB_RECURSE HEADER_FILES project/include/*.h project/include/*.hpp)
file(GLOB_RECURSE RESOURCES project/resources/*)

include(ImportLibs.cmake)

add_subdirectory(ECS)
add_subdirectory(glad)
add_subdirectory(GameEngine)

include_directories(glad/include)
include_directories(ECS/include)
include_directories(${GLM_INCLUDE_DIRS})
include_directories(GameEngine/include)
include_directories(project/include)

add_executable(main ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(main PRIVATE ECS)
target_link_libraries(main PRIVATE GameEngine)
target_link_libraries(main PRIVATE glad)
target_link_libraries(main PRIVATE ${CMAKE_DL_LIBS})
if (UNIX AND NOT APPLE)
	target_link_libraries(main PRIVATE ${X11_LIBRARIES})
endif()

install(FILES ${RESOURCES}
		TYPE DATA)
install(TARGETS main
		TYPE RUNTIME)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin/)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/share/)
foreach(item IN LISTS RESOURCES)
	configure_file(${item} ${CMAKE_BINARY_DIR}/share/ COPYONLY)
endforeach()