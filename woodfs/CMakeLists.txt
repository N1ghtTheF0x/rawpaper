add_library(woodfs SHARED woodfs.hpp woodfs.cpp)

set_target_properties(woodfs
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${WORKSPACE_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${WORKSPACE_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${WORKSPACE_DIR}/bin"
)