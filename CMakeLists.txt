cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(ResourceManager)

add_executable(embed_resource src/embed_resource.cpp)


set(RESOURCE_MANAGER_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include" PARENT_SCOPE)

function(rm_embed_resources output_resources_list)
  if(${ARGC} EQUAL 1)
    add_custom_command(
      OUTPUT "__resources__config.cpp"
      COMMAND embed_resource "-config"
      VERBATIM)

    set(${output_resources_list} "__resources__config.cpp" PARENT_SCOPE)
    message(WARNING "ResourceManager::rm_embed_resources: No resources provided")
  else()
    set(input_names)
    foreach(input_file_name ${ARGN})
      file(RELATIVE_PATH rel_bin_input_file_name "${CMAKE_BINARY_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/${input_file_name}")
      set(output_file_name "${input_file_name}.cpp")

      add_custom_command(
        OUTPUT "${output_file_name}"
        COMMAND embed_resource "-data" "${rel_bin_input_file_name}" "${input_file_name}" "${output_file_name}"
        DEPENDS "${input_file_name}"
        VERBATIM)

      list(APPEND input_names "${input_file_name}")
      list(APPEND result "${output_file_name}")
    endforeach()
    
    add_custom_command(
      OUTPUT "__resources__config.cpp"
      COMMAND embed_resource "-config" "${input_names}"
      DEPENDS ${result}
      VERBATIM)

    list(APPEND result "__resources__config.cpp")
    set(${output_resources_list} ${result} PARENT_SCOPE)
  endif()
endfunction()