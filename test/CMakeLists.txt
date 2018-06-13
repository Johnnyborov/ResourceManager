cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(test_main)

add_subdirectory(".." "${CMAKE_BINARY_DIR}/ResourceManager")
include_directories(${RESOURCE_MANAGER_INCLUDE_DIRS})

rm_embed_resources(RESOURCES "res.txt" "res2.txt" "resources/res.txt")

#add_definitions(-DRM_NO_EXCEPTIONS)
#set_source_files_properties(${RESOURCE_MANAGER_RESOURCES_CONFIG_FILE} PROPERTIES COMPILE_DEFINITIONS RM_NO_EXCEPTIONS)

add_executable(${PROJECT_NAME} src/test_main.cpp ${RESOURCES})