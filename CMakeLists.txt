cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(ResourceManager)

add_executable(embed_resource embed_resource.cpp)

function(rm_embed_resources output_resources_list)
  add_custom_command(
    OUTPUT "1.cpp"
    COMMAND embed_resource "1.cpp"
    DEPENDS "${PROJECT_SOURCE_DIR}/test_resource.txt"
    VERBATIM)

  set(${output_resources_list} "1.cpp" PARENT_SCOPE)
endfunction()