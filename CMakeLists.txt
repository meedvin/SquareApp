cmake_minimum_required(VERSION 3.17)
project(CalcSquare LANGUAGES C)

add_executable(Square_App 
                src/main.c
                src/square_app.c)

install(TARGETS Square_App RUNTIME DESTINATION bin)

include(CTest)
enable_testing()

include(FetchContent)
FetchContent_Declare(
    Unity
    GIT_REPOSITORY https://github.com/ThrowTheSwitch/Unity.git
    GIT_TAG        v2.6.0
    GIT_SHALLOW    TRUE
)
FetchContent_MakeAvailable(Unity)   

file(GLOB TEST_SOURCES tests/test.c)  
add_executable(unit_tests 
                ${TEST_SOURCES} 
                ${PROJECT_SOURCE_DIR}/src/square_app.c)

target_link_libraries(unit_tests PRIVATE unity)

add_test(NAME ALL_TESTS COMMAND unit_tests)

set_property(TEST ALL_TESTS PROPERTY ENVIRONMENT "CTEST_OUTPUT_ON_FAILURE=1")
