cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(ResourceManager)

add_executable(embed_resource embed_resource.cpp)
if(MINGW)
  target_link_libraries(embed_resource stdc++fs)
endif()


set(RESOURCE_MANAGER_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)

function(rm_embed_resources output_resources_list)
  if(${ARGC} EQUAL 1)
    message(WARNING "ResourceManager::rm_embed_resources: No resources provided")
  else()
    set(input_names)
    foreach(input_file_name ${ARGN})
      set(output_file_name "${input_file_name}.cpp")

      add_custom_command(
        OUTPUT "${output_file_name}"
        COMMAND embed_resource "-data" "${CMAKE_CURRENT_SOURCE_DIR}/${input_file_name}" "${output_file_name}"
        DEPENDS "${input_file_name}"
        VERBATIM)

      list(APPEND input_names "${input_file_name}")
      list(APPEND result "${output_file_name}")
    endforeach()
    
    add_custom_command(
      OUTPUT "resources_config.cpp"
      COMMAND embed_resource "-config" "${input_names}"
      DEPENDS ${result}
      VERBATIM)

    list(APPEND result "resources_config.cpp")
    set(${output_resources_list} ${result} PARENT_SCOPE)
  endif()
endfunction()