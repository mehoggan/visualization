# Download and unpack opengl_graphics at configure time
execute_process(COMMAND ${CMAKE_COMMAND}
  -G "${CMAKE_GENERATOR}" .
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/opengl_graphics-download)
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/opengl_graphics-download)


# Add opengl_graphics directly to our build. This adds
# the following targets: opengl_graphics
add_subdirectory(${CMAKE_BINARY_DIR}/opengl_graphics-src/
  ${CMAKE_BINARY_DIR}/opengl_graphics-build)

# The opengl_graphics target carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
include_directories("${CMAKE_CURRENT_BINARY_DIR}/opengl_graphics-src/include")

