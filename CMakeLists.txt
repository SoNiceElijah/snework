
cmake_minimum_required(VERSION 3.1)

set(PROJECT_NAME "SNE sci work app")

project(PROJECT_NAME)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG    "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE  "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY          "${CMAKE_BINARY_DIR}/bin")

file(GLOB HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/header/*.h")
file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/source/*.c")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/header)

set(TARGET_NAME "sneapp")

set(GCC_OPT_FLAGS "-march='skylake' -O3")

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(${TARGET_NAME} ${HEADERS} ${SOURCES})
set_target_properties(${TARGET_NAME} PROPERTIES COMPILE_FLAGS ${GCC_OPT_FLAGS})
target_link_libraries(${TARGET_NAME} "m")
target_link_libraries(${TARGET_NAME} Threads::Threads)
