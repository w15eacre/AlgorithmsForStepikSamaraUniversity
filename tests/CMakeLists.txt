project(AlgorithmsTest)

find_package(GTest REQUIRED)

FILE(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

set(SRC ${CMAKE_SOURCE_DIR}/src)
set(RESOURCE_PATH ${CMAKE_SOURCE_DIR}/resources)
set(ALG_PATH ${SRC}/algorithms)
set(SOURCES
        input_stream_device_test.cpp
        brace_sequence_algorithm_test.cpp
        scheduler_algorithm_test.cpp
        room_scheduler_algorithm_test.cpp
        gas_station_test.cpp
        knapsack_problem_test.cpp)

configure_file (${CMAKE_CURRENT_SOURCE_DIR}/test_config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/test_config.h @ONLY)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${SRC})
target_link_libraries(${PROJECT_NAME} PRIVATE GTest::GTest GTest::Main AlgorithmIntroduction)