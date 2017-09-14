# Download and unpack glm at configure time
execute_process(COMMAND ${CMAKE_COMMAND}
  -G "${CMAKE_GENERATOR}" .
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/glm-download)
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/glm-download)


# Add glm directly to our build. This adds
# the following targets: glm
add_subdirectory(${CMAKE_BINARY_DIR}/glm-src
  ${CMAKE_BINARY_DIR}/glm-build)

# The glm target carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
include_directories("${CMAKE_BINARY_DIR}/glm-src/")

