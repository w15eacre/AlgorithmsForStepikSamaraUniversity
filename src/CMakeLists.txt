project(AlgorithmIntroduction)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(ALGORITHMS_PATH ${CMAKE_CURRENT_SOURCE_DIR}/algorithms)

set(SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/input_stream_device.cpp
        ${ALGORITHMS_PATH}/brace_sequence_algorithm.cpp
        ${ALGORITHMS_PATH}/scheduler_algorithm.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/file_reader.cpp
        ${ALGORITHMS_PATH}/room_scheduler.cpp
        ${ALGORITHMS_PATH}/gas_station.cpp)

set(HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/input_stream_device.h
        ${CMAKE_CURRENT_SOURCE_DIR}/i_input_stream_device.h
        ${ALGORITHMS_PATH}/algorithm_concept.h
        ${ALGORITHMS_PATH}/algorithm_executor.h
        ${ALGORITHMS_PATH}/brace_sequence_algorithm.h
        ${ALGORITHMS_PATH}/scheduler_algorithm.h
        ${CMAKE_CURRENT_SOURCE_DIR}/file_reader.h
        ${ALGORITHMS_PATH}/room_scheduler.h
        ${ALGORITHMS_PATH}/gas_station.h)

add_library(${PROJECT_NAME} ${SOURCES} utils.h)