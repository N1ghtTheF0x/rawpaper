project(WoodFS VERSION 1.0.0)
add_library(woodfs STATIC woodfs.hpp woodfs.cpp)

add_dependencies(woodfs putils)

target_include_directories(woodfs PUBLIC ${WORKSPACE_DIR}/putils)
target_link_libraries(woodfs PUBLIC putils)

add_executable(cwoodfs cwoodfs.cpp)

add_dependencies(cwoodfs woodfs)

target_link_libraries(cwoodfs woodfs)
target_include_directories(cwoodfs PUBLIC .)