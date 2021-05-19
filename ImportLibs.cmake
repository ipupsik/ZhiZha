set(${CMAKE_FIND_USE_PACKAGE_ROOT_PATH} FALSE)

# These libs should be installed manually

# Common libs for any platform
set(CMAKE_PREFIX_PATH ${PROJECT_SOURCE_DIR}/Lib/Common)

find_package(glm REQUIRED)
if (${glm_FOUND})
    message(STATUS "Found GLM ${glm_VERSION} in ${glm_DIR}")
endif()

# Platform-dependent libs
if (UNIX AND NOT APPLE)
    set(CMAKE_PREFIX_PATH ${PROJECT_SOURCE_DIR}/Lib/Linux)
    find_package(X11 REQUIRED)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-pthread")
elseif (WIN32)
    set(CMAKE_PREFIX_PATH ${PROJECT_SOURCE_DIR}/Lib/Windows)
elseif(APPLE)
    set(CMAKE_PREFIX_PATH ${PROJECT_SOURCE_DIR}/Lib/MacOS)
endif()

find_package(SFML COMPONENTS system window graphics REQUIRED)