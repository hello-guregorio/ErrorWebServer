cmake_minimum_required(VERSION 3.0)
project(ErrorWebServer)

# some compiler option
SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

# include path
include_directories(${PROJECT_SOURCE_DIR}/inc)
include_directories("/usr/include/mysql")

# src path
aux_source_directory(${PROJECT_SOURCE_DIR}/src src_dirs)

# link_directories(${PROJECT_SOURCE_DIR}/lib)

# which dir to compiler
add_subdirectory(${PROJECT_SOURCE_DIR}/src)
add_subdirectory(test)
# executable file path
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# spdlog
find_package(spdlog REQUIRED)

add_executable(ErrorWebServer ${src_dirs})

target_link_libraries(ErrorWebServer 
    PRIVATE spdlog::spdlog $<$<BOOL:${MINGW}>:ws2_32> 
    mysqlclient
    parse_cfg
    mysql_pool
)