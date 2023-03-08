message("thread_pool--${PROJECT_SOURCE_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
add_library(thread_pool SHARED ./thread_pool.cc)