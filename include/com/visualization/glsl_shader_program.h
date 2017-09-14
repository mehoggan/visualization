#ifndef COM_VISUALIZATION_GLSL_SHADER_PROGRAM_H_INCLUDED
#define COM_VISUALIZATION_GLSL_SHADER_PROGRAM_H_INCLUDED

#include "declspec.h"

#include <QOpenGLFunctions>

#include <string>
#include <vector>

#ifdef __APPLE__
  #include <OpenGL/gl.h>
#elif __linux__
  #include <GL/gl.h>
#endif

namespace com
{
  namespace visualization
  {
    class DLLSPEC_COM_VISUALIZATION glsl_shader_program
    {
    public:
      glsl_shader_program();
      ~glsl_shader_program();

      void add_vertex_shader_source(const std::string &src);
      void add_vertex_shader_sources(const std::vector<std::string> &src);

      void add_fragment_shader_source(const std::string &src);
      void add_fragment_shader_sources(const std::vector<std::string> &src);

      bool create_program(QOpenGLFunctions &gl_functions);

      GLuint id() const;
      GLuint vertex_shader_id() const;
      GLuint fragment_shader_id() const;

    private:
      std::vector<std::string> vertex_shader_sources_;
      std::vector<std::string> fragment_shader_sources_;

      GLuint shader_program_;
      GLuint vertex_shader_;
      GLuint fragment_shader_;
      std::string log_tag_;
    };
  }
}

#endif
