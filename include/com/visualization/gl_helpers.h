#ifndef COM_VISUALIZATION_GL_HELPERS_H_INCLUDED
#define COM_VISUALIZATION_GL_HELPERS_H_INCLUDED

#include "com/visualization/logging.h"

#include <QOpenGLFunctions>

#include <cassert>
#include <iostream>
#include <string>
#include <utility>

#ifdef __APPLE__
  #include <OpenGL/gl.h>
#elif __linux__
  #include <GL/gl.h>
#endif

#ifndef DEBUG_GL
  #define DEBUG_GL 1
#endif

#if DEBUG_GL
#define GL_OUTPUT(func_string, log_tag) \
  std::string tag = log_tag; \
  com::visualization::logging::error(tag, "file =", __FILE__, \
    "line =", __LINE__, \
    "error =", error, \
    "opengl function =", func_string);
#else
#define GL_OUTPUT {int x = 0; x = x;}
#endif

#define GL_CALL(gl_functions, func, log_tag) do { \
    GLint error; \
    std::string func_string = func; \
    while ((error = gl_functions.glGetError()) != 0) { \
      GL_OUTPUT(func_string, log_tag); \
    } \
  } while(false);

#define GL_CALL_BASE(func, log_tag) do { \
    GLint error; \
    std::string func_string = func; \
    while ((error = glGetError()) != 0) { \
      GL_OUTPUT(func_string, log_tag); \
    } \
  } while(false);
#endif
