# Download and unpack jsoncpp at configure time
execute_process(COMMAND ${CMAKE_COMMAND}
  -G "${CMAKE_GENERATOR}" .
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/jsoncpp-download)
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/jsoncpp-download)


# Add jsoncpp directly to our build. This adds
# the following targets: jsoncpp
add_subdirectory(${CMAKE_BINARY_DIR}/jsoncpp-src/
  ${CMAKE_BINARY_DIR}/jsoncpp-build)

# The jsoncpp target carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
include_directories("${jsoncpp_SOURCE_DIR}/include")

