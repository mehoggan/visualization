function(copy_resources target)
  set(options "")
  set(oneValueArgs SOURCE_FILE DESTINATION_DIR)
  set(multiValueArgs "")
  cmake_parse_arguments(copy_resources "${options}" "${oneValueArgs}"
    "${multiValueArgs}" ${ARGN})

  string(STRIP "${copy_resources_DESTINATION_DIR}"
    copy_resources_DESTINATION_DIR
  )
  string(STRIP "${copy_resources_SOURCE_FILE}"
    copy_resources_SOURCE_FILE
  )

  message(STATUS "\${copy_resources_SOURCE_FILE} = --"
    "${copy_resources_SOURCE_FILE}--")
  message(STATUS "\${copy_resources_DESTINATION_DIR} = --"
    "${copy_resources_DESTINATION_DIR}--")

  if(copy_resources_DESTINATION_DIR STREQUAL "")
    add_custom_command(TARGET ${target} POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy ${copy_resources_SOURCE_FILE}
        ${CMAKE_CURRENT_BINARY_DIR}
    )
    message(STATUS "Copying ${copy_resources_SOURCE_FILE} to default dir of "
      "${CMAKE_CURRENT_BINARY_DIR}")
  else()
    add_custom_command(TARGET ${target} POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy ${copy_resources_SOURCE_FILE}
        ${copy_resources_DESTINATION_DIR}
    )
    message(STATUS "Copying ${copy_resources_SOURCE_FILE} to user dir of "
      "${copy_resources_DESTINATION_DIR}")
  endif()
endfunction()
