# Download and unpack opengl_math at configure time
execute_process(COMMAND ${CMAKE_COMMAND}
  -G "${CMAKE_GENERATOR}" .
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/opengl_math-download)
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/opengl_math-download)


# Add opengl_math directly to our build. This adds
# the following targets: opengl_math
add_subdirectory(${CMAKE_BINARY_DIR}/opengl_math-src/
  ${CMAKE_BINARY_DIR}/opengl_math-build)

# The opengl_math target carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
include_directories("${CMAKE_CURRENT_BINARY_DIR}/opengl_math-src/include")

