cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(test_main)

add_subdirectory(".." "${CMAKE_BINARY_DIR}/ResourceManager")
include_directories(${RESOURCE_MANAGER_INCLUDE_DIRS})

rm_embed_resources(RESOURCES "res1.txt" "res2.txt")

add_executable(${PROJECT_NAME} test_main.cpp ${RESOURCES})