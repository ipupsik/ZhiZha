file(GLOB_RECURSE HEADER_FILES include/*.h)
file(GLOB_RECURSE HEADER_FILES include/Components/*.h)
file(GLOB_RECURSE SOURCE_FILES src/*.cpp)

add_library(GameEngine ${SOURCE_FILES} ${HEADER_FILES} "src/Systems/ActorRenderSystem.cpp")
include_directories(../ECS/include)
include_directories(../glm/include)

target_include_directories(GameEngine
		PUBLIC    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		INTERFACE $<INSTALL_INTERFACE:include>)
target_link_libraries(GameEngine PUBLIC sfml-window sfml-graphics sfml-system)
