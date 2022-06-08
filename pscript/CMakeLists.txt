project(PScript VERSION 1.0.0)

file(GLOB_RECURSE PSCRIPT_CPP_FILES "src/*.cpp")

add_library(pscript STATIC ${PSCRIPT_CPP_FILES})

add_dependencies(pscript putils)

target_include_directories(pscript PUBLIC include)
target_link_libraries(pscript PUBLIC putils)
target_include_directories(pscript PUBLIC ${WORKSPACE_DIR}/putils)

add_executable(pscriptc pscriptc.cpp)

target_link_libraries(pscriptc PUBLIC pscript)
target_include_directories(pscriptc PUBLIC include)