cmake_minimum_required(VERSION 3.0.0)
project(rawpaper VERSION 0.1.0)

set(WORKSPACE_DIR ${PROJECT_SOURCE_DIR} CACHE INTERNAL "WORKSPACE_DIR")

add_subdirectory(woodfs)
add_subdirectory(engine)