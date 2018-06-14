# Copyright (c) 2018 Johnny Borov <JohnnyBorov@gmail.com>. Released under MIT License.

cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(test_main)

if(MSVC)
  add_compile_options(-WX -W4)
elseif(MINGW)
  add_compile_options(-Werror -Wall -Wextra -Wno-ignored-qualifiers -pedantic)
endif()

add_subdirectory(".." "${CMAKE_BINARY_DIR}/ResourceManager")
include_directories(${RESOURCE_MANAGER_INCLUDE_DIRS})

rm_embed_resources(RESOURCES "res.txt" "res2.txt" "resources/res.txt")

#add_definitions(-DRM_NO_EXCEPTIONS)
#set_source_files_properties(${RESOURCE_MANAGER_RESOURCES_CONFIG_FILE} PROPERTIES COMPILE_DEFINITIONS RM_NO_EXCEPTIONS)

add_executable(${PROJECT_NAME} src/test_main.cpp ${RESOURCES})