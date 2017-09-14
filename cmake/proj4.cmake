# Download and unpack proj4 at configure time
execute_process(COMMAND ${CMAKE_COMMAND}
  -G "${CMAKE_GENERATOR}" .
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/proj4-download)
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/proj4-download)


# Add proj4 directly to our build. This adds
# the following targets: proj4
add_subdirectory(${CMAKE_BINARY_DIR}/proj4-src
  ${CMAKE_BINARY_DIR}/proj4-build)

# The proj4 target carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
include_directories("${proj4_SOURCE_DIR}/include")

