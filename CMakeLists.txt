cmake_minimum_required(VERSION 3.0)
project(ErrorWebServer)

# include path
include_directories(${PROJECT_SOURCE_DIR}/inc)
include_directories("/usr/include/mysql")

# src path
aux_source_directory(${PROJECT_SOURCE_DIR}/src src_dirs)

# link_directories(${PROJECT_SOURCE_DIR}/lib)

# which dir to compiler
add_subdirectory(${PROJECT_SOURCE_DIR}/src)

# executable file path
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# spdlog
if(NOT TARGET spdlog)
    find_package(spdlog REQUIRED)
endif()

add_executable(ErrorWebServer ${src_dirs})

target_link_libraries(ErrorWebServer 
    PRIVATE spdlog::spdlog $<$<BOOL:${MINGW}>:ws2_32> 
    mysqlclient
    parse_cfg
)