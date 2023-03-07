message("parse--${PROJECT_SOURCE_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
add_library(parse_cfg SHARED ./parse_cfg.cc)