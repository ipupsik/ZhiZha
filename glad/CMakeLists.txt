file(GLOB_RECURSE SOURCE_FILES src/*.c)

include_directories(include)

add_library(glad ${SOURCE_FILES})
target_include_directories(glad
        PUBLIC $<BUILD_INTERFACE:${GLAD_INCLUDE_DIR}>
        INTERFACE $<INSTALL_INTERFACE:include/glad>)
set_target_properties(glad PROPERTIES
        LINKER_LANGUAGE C)