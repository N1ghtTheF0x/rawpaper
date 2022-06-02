cmake_minimum_required(VERSION 3.0.0)
project(rawpaper VERSION 0.1.0)

set(WORKSPACE_DIR ${PROJECT_SOURCE_DIR} CACHE INTERNAL "WORKSPACE_DIR")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${WORKSPACE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${WORKSPACE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${WORKSPACE_DIR}/bin)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(OS_NAME "linux" CACHE INTERNAL OS_NAME)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(OS_NAME "darwin" CACHE INTERNAL OS_NAME)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(OS_NAME "win32" CACHE INTERNAL OS_NAME)
endif()

add_subdirectory(putils)
add_subdirectory(woodfs)
add_subdirectory(engine)

add_executable(rawpaper main.cpp)
target_include_directories(rawpaper PUBLIC ${WORKSPACE_DIR}/engine/include ${WORKSPACE_DIR}/woodfs)
target_link_libraries(rawpaper PUBLIC engine woodfs)