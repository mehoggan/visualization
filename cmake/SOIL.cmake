# Download and unpack SOIL at configure time
execute_process(COMMAND ${CMAKE_COMMAND}
  -G "${CMAKE_GENERATOR}" .
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/SOIL-download)
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/SOIL-download)

# Add SOIL directly to our build
add_subdirectory(${CMAKE_BINARY_DIR}/SOIL-src
  ${CMAKE_BINARY_DIR}/SOIL-build)

# The gtest/gmock targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
include_directories("${CMAKE_BINARY_DIR}/SOIL-src/src/")

