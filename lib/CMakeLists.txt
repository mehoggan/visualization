cmake_minimum_required(VERSION 3.0.2)
include_directories(../)
include_directories(../include/)
include_directories(${gtest_SOURCE_DIR}/include)
include_directories(${CMAKE_BINARY_DIR}/proj4-src/src)

# For Qt
find_package(Qt5Widgets REQUIRED)
find_package(Qt5OpenGL REQUIRED)
find_package(OpenGL REQUIRED)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
include_directories(${Qt5Widgets_INCLUDE_DIRS})
include_directories(${Qt5OpenGL_INCLUDE_DIRS})

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

#For JsonCPP
include_directories(${CMAKE_BINARY_DIR}/jsoncpp-src/include)

set(SRC
  application.cpp
  camera.cpp
  geometries/sphere.cpp
  geometry.cpp
  gl_helpers.cpp
  glsl_shader_program.cpp
  gl_widget.cpp
  logging.cpp
  log_helpers.cpp
  main_window.cpp
  scene.cpp
  scenes/indexed_rainbow_rectangle.cpp
  scenes/indexed_rainbow_sphere.cpp
  scenes/indexed_rainbow_textured_rectangle.cpp
  scenes/multi_textured_rectangle.cpp
  scenes/projected_textured_rectangle.cpp
  scenes/rainbow_triangle.cpp
  scenes/simple_triangle.cpp
)
set(MOC_SRC "")  # Filled in, in the foreach loop below.

set(HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../include/com/visualization)
foreach(q_obj_header ${Q_OJBECT_HEADERS})
  qt5_wrap_cpp(tmp_var ${HEADER_DIR}/${q_obj_header})
  list(APPEND MOC_SRC ${tmp_var})
endforeach()

add_definitions(${Qt5Widgets_DEFINITIONS})

if (BUILD_SHARED_LIBS)
  add_library(
    com_visualization
    SHARED
    ${SRC}
    ${MOC_SRC}
  )
  add_definitions(
    -DCOM_VISUALIZATION_SHARED
    -DCOM_VISUALIZATION_EXPORTS
  )
else()
  add_library(
    com_visualization
    STATIC
    ${SRC}
    ${MOC_SRC}
  )
  add_definitions(
    -DCOM_VISUALIZATION_STATIC
  )
endif()

qt5_use_modules(
  com_visualization
  OpenGL
  Widgets
)

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

target_link_libraries(com_visualization
  ${QT_LIBRARIES}
  ${Boost_LIBRARIES}
  SOIL
  jsoncpp
  proj
  s2
  ${OPENGL_LIBRARIES}
)
