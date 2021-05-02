file(GLOB_RECURSE SOURCE_FILES src/*.cpp)

set(CMAKE_CXX_STANDARD 20)
include_directories(include)
include_directories(lib/glad/include)

add_library(GameEngine ${SOURCE_FILES} lib/glad/src/glad.c)

find_package(SFML COMPONENTS system window graphics REQUIRED)

target_include_directories(GameEngine PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
        $<INSTALL_INTERFACE:include>)
target_link_libraries(GameEngine PUBLIC glut ${CMAKE_DL_LIBS} sfml-window sfml-graphics sfml-system)
