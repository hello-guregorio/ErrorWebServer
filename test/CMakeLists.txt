cmake_minimum_required(VERSION 3.0)

enable_testing()
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
include(GoogleTest)
find_package(GTest REQUIRED)
find_package(spdlog REQUIRED)

add_executable(Test_webserver test_main.cc)

target_link_libraries(Test_webserver
    ${GTEST_BOTH_LIBRARIES}
    spdlog::spdlog $<$<BOOL:${MINGW}>:ws2_32> 
    pthread
    parse_cfg
    mysql_pool
    mysqlclient
)

gtest_discover_tests(Test_webserver)