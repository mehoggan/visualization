cmake_minimum_required(VERSION 3.0.2)
project(com_visualization)

option(
  BUILD_SHARED_LIBS
  "Build shared libraries over static library."
  ON
)
option(
  VISUALIZATION_VISUALIZATION_TESTS
  "Build unit tests."
  ON
)
option(
  VISUALIZATION_VISUALIZATION_BINDINGS
  "Build all bindings for the native library."
  ON
)

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  message(STATUS "Setting up OpenSSL for OSX build.")
  set(OPENSSL_ROOT_DIR "/usr/local/Cellar/openssl/1.0.2m")
  set(OPENSSL_LIBRARIES "/usr/local/Cellar/openssl/1.0.2m/lib")
  set(OPENSSL_INCLUDE_DIR "/usr/local/Cellar/openssl/1.0.2m/include")
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  set(OPENSSL_ROOT_DIR "/usr/lib/ssl/")
  set(OPENSSL_LIB_DIR "/usr/local/lib/ssl")
endif()

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  set(CMAKE_MACOSX_RPATH 1)
endif()

find_package(PkgConfig REQUIRED)
pkg_search_module(OPENSSL REQUIRED openssl)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.opengl_graphics.txt.in
  ${CMAKE_BINARY_DIR}/opengl_graphics-download/CMakeLists.txt)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/opengl_graphics.cmake)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.opengl_math.txt.in
  ${CMAKE_BINARY_DIR}/opengl_math-download/CMakeLists.txt)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/opengl_math.cmake)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.SOIL.txt.in
  ${CMAKE_BINARY_DIR}/SOIL-download/CMakeLists.txt)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/SOIL.cmake)
link_directories("${CMAKE_BINARY_DIR}/SOIL-build/")

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.glm.txt.in
  ${CMAKE_BINARY_DIR}/glm-download/CMakeLists.txt)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/glm.cmake)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.proj4.txt.in
  ${CMAKE_BINARY_DIR}/proj4-download/CMakeLists.txt)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/proj4.cmake)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.s2-geometry.txt.in
  ${CMAKE_BINARY_DIR}/s2-geometry-download/CMakeLists.txt)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/s2-geometry.cmake)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.jsoncpp.txt.in
  ${CMAKE_BINARY_DIR}/jsoncpp-download/CMakeLists.txt)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/jsoncpp.cmake)
link_directories("${CMAKE_BINARY_DIR}/jsoncpp-build/src/lib_json/")

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/c++11.cmake)

include_directories(${gtest_SOURCE_DIR}/include)

add_subdirectory(include)
add_subdirectory(lib)
add_subdirectory(bin)

if(VISUALIZATION_VISUALIZATION_TESTS)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.googletest.txt.in
    ${CMAKE_BINARY_DIR}/googletest-download/CMakeLists.txt)
  include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/googletest.cmake)
  add_subdirectory(tests)
endif()
