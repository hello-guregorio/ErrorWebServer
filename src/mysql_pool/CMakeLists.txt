message("mysql_pool--${PROJECT_SOURCE_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
add_library(mysql_pool SHARED ./mysql_pool.cc)