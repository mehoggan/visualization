cmake_minimum_required(VERSION 3.0.2)

find_program(valgrind REQUIRED)
set(CTEST_MEMORYCHECK_COMMAND "/usr/bin/valgrind") 
set(CTEST_MEMORYCHECK_COMMAND_OPTIONS "--trace-children=yes
  --leak-check=full")
include(CTest)
enable_testing()
add_test(unit_test unit_test --report_level=no --log_level=all
  --output_format=xml --log_sink=${CMAKE_BINARY_DIR}/test_logs/${name}.xml)
include_directories(../include)
include_directories(../)
include_directories(${gtest_SOURCE_DIR}/include)

#For Boost
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(
  Boost
  COMPONENTS log log_setup thread date_time filesystem system
  REQUIRED
)
include_directories(${Boost_INCLUDE_DIRS})

set(SRC
  main.cpp
  test_camera.cpp
  test_logging.cpp
)

add_executable(unit_test ${SRC})

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/win32.cmake)
  add_definitions(
    -D_CRT_SECURE_NO_WARNINGS
  )
else()
  set_target_properties(
    com_visualization
    PROPERTIES COMPILE_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall \
    -fno-strict-aliasing"
  )
endif()

target_link_libraries(unit_test
  com_visualization
  ${Boost_LIBRARIES}
  gtest
  gtest_main
  gmock
  gmock_main
)
target_link_libraries(unit_test
  debug com_visualization
  ${Boost_LIBRARIES}
  gtest
  gtest_main
  gmock
  gmock_main
)
