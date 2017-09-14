cmake_minimum_required(VERSION 3.0.2)
include_directories(../../)
include_directories(../../include/)

#For Boost
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(
  Boost
  COMPONENTS log log_setup thread date_time filesystem system
  REQUIRED
)
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

set(SIMPLE_TRIANGLE_SRC
  simple_triangle.cpp
)

add_executable(com_visualizer_simple_triangle
  ${SIMPLE_TRIANGLE_SRC}
)

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  include(${CMAKE_SOURCE_DIR}/cmake/win32.cmake)
  add_definitions(
    -D_CRT_SECURE_NO_WARNINGS
  )
else()
  set_target_properties(
    com_visualizer_simple_triangle
    PROPERTIES COMPILE_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall \
    -fno-strict-aliasing -std=c++11"
  )
endif()

target_link_libraries(com_visualizer_simple_triangle
  com_visualization
  ${Boost_LIBRARIES}
)

include("${CMAKE_CURRENT_SOURCE_DIR}/../../cmake/utils.cmake")
copy_resources(com_visualizer_simple_triangle
  SOURCE_FILE "${CMAKE_CURRENT_SOURCE_DIR}/../../resources/sample.png"
)
copy_resources(com_visualizer_simple_triangle
  SOURCE_FILE "${CMAKE_CURRENT_SOURCE_DIR}/../../resources/sample2.png"
)

