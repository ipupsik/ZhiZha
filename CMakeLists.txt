CMAKE_MINIMUM_REQUIRED(VERSION 3.19)
project(zhizha C CXX)
set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCE_FILES project/src/*.cpp project/src/*.c)
file(GLOB_RECURSE HEADER_FILES project/include/*.h project/include/*.hpp)
file(GLOB_RECURSE RESOURCES project/resources/*)

include(ImportLibs.cmake)

add_subdirectory(glm)

include_directories(glm)
add_subdirectory(ECS)
add_subdirectory(glad)

include_directories(glad/include)
include_directories(ECS/include)
add_subdirectory(GameEngine)
add_subdirectory(PhysicsEngine)

include_directories(GameEngine/include)
include_directories(PhysicsEngine/include)
include_directories(project/include)

add_executable(main ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(main PRIVATE ECS GameEngine glad PhysicsEngine ${CMAKE_DL_LIBS} glm::glm)
if (UNIX AND NOT APPLE)
    target_link_libraries(main PRIVATE ${X11_LIBRARIES})
endif ()

install(FILES ${RESOURCES}
        TYPE DATA)
install(TARGETS main
        TYPE RUNTIME)

if (NOT MSVC_IDE)
    set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin/)
endif ()
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/share/)
foreach (item IN LISTS RESOURCES)
    configure_file(${item} ${CMAKE_BINARY_DIR}/share/ COPYONLY)
endforeach ()