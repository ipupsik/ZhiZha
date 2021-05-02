file(GLOB_RECURSE SOURCE_FILES src/*.cpp)

set(CMAKE_CXX_STANDARD 20)
include_directories(include)
include_directories(lib/glad/include)

add_library(GameEngine ${SOURCE_FILES} lib/glad/src/gl.c)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

target_include_directories(GameEngine PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
        $<INSTALL_INTERFACE:include>)
target_link_libraries(GameEngine PUBLIC glfw OpenGL::GL ${CMAKE_DL_LIBS})
