cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(ResourceManager)

add_executable(embed_resource embed_resource.cpp)

if(MINGW)
  target_link_libraries(embed_resource stdc++fs)
endif()

function(rm_embed_resources output_resources_list)
  if(${ARGC} EQUAL 1)
    message(FATAL_ERROR "ResourceManager::rm_embed_resources: No resources provided")
  elseif(${ARGC} EQUAL 2)
    set(ER_MODE "-both")
  else()
    set(ER_MODE "-start")
  endif()

  add_custom_command(
    OUTPUT "resources_config.cpp" "1.cpp"
    COMMAND embed_resource  ${ER_MODE} "${PROJECT_SOURCE_DIR}/test_resource.txt" "1.cpp"
    DEPENDS "${PROJECT_SOURCE_DIR}/test_resource.txt"
    VERBATIM)

  set(${output_resources_list} "resources_config.cpp" "1.cpp" PARENT_SCOPE)
endfunction()