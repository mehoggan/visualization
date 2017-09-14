# Download and unpack s2-geometry at configure time
execute_process(COMMAND ${CMAKE_COMMAND}
  -G "${CMAKE_GENERATOR}" .
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/s2-geometry-download)
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/s2-geometry-download)


# Add s2-geometry directly to our build. This adds
# the following targets: s2-geometry
add_subdirectory(${CMAKE_BINARY_DIR}/s2-geometry-src/geometry
  ${CMAKE_BINARY_DIR}/s2-geometry-build)

# The s2-geometry target carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
include_directories("${s2-geometry_SOURCE_DIR}/include")

