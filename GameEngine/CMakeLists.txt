file(GLOB_RECURSE SOURCE_FILES src/*.cpp)

include_directories(include)
include_directories(lib/glad/include)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(GameEngine ${SOURCE_FILES})
target_link_libraries(GameEngine -lglfw -lX11 -lgl -ldl)
