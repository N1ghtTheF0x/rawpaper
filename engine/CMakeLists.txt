file(GLOB_RECURSE ENGINE_CPP_FILES "src/${OS_NAME}/*.cpp")
file(GLOB_RECURSE ENGINE_HPP_FILES "include/*.hpp")

add_library(engine SHARED ${ENGINE_CPP_FILES} ${ENGINE_HPP_FILES})

add_dependencies(engine putils)

target_link_directories(engine PUBLIC ${WORKSPACE_DIR}/putils)
target_link_libraries(engine PUBLIC putils)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    find_package(X11 REQUIRED)
    find_package(OpenGL REQUIRED)

    message(STATUS "X11_FOUND = ${X11_FOUND}")
    message(STATUS "X11_INCLUDE_DIR = ${X11_INCLUDE_DIR}")
    message(STATUS "X11_LIBRARIES = ${X11_LIBRARIES}")

    target_include_directories(engine PUBLIC ${X11_INCLUDE_DIR})
    target_link_libraries(engine PUBLIC ${X11_LIBRARIES} ${OPENGL_LIBRARAY} ${OPENGL_glx_LIBRARY})
    target_compile_definitions(engine PUBLIC "IS_LINUX")
endif()
if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    target_compile_definitions(engine PUBLIC "IS_MACOS")
endif()
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_compile_definitions(engine PUBLIC "IS_WINDOWS")
endif()