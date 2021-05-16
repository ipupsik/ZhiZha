file(GLOB_RECURSE HEADER_FILES include/*.h)
file(GLOB_RECURSE SOURCE_FILES src/*.cpp)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML COMPONENTS system window graphics REQUIRED)

add_library(GameEngine ${SOURCE_FILES} ${HEADER_FILES})
include_directories(../ECS/include)

target_include_directories(GameEngine
		PUBLIC    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		INTERFACE $<INSTALL_INTERFACE:include>)
target_link_libraries(GameEngine PUBLIC sfml-window sfml-graphics sfml-system)
