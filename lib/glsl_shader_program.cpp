#include "com/visualization/glsl_shader_program.h"

#include "com/visualization/gl_helpers.h"

#include <iterator>

namespace com
{
  namespace visualization
  {
    namespace detail
    {
      void compile_shader(GLuint &shader, QOpenGLFunctions gl_functions,
        GLenum shader_type, const std::vector<std::string> src,
        const std::string &log_tag)
      {
        const GLchar *shader_addr = src[0].c_str();
        shader = gl_functions.glCreateShader(shader_type);
        GL_CALL(gl_functions, "glCreateShader", log_tag)
        gl_functions.glShaderSource(shader, src.size(), &shader_addr, 0);
        GL_CALL(gl_functions, "glShaderSource", log_tag)
        gl_functions.glCompileShader(shader);
        GL_CALL(gl_functions, "glCompileShader", log_tag)
      }

      bool check_if_shader_compiled(GLuint shader,
        QOpenGLFunctions &gl_functions, const std::string &log_tag)
      {
        bool ret = true;

        GLint is_compiled = 0;
        gl_functions.glGetShaderiv(shader, GL_COMPILE_STATUS, &is_compiled);
        GL_CALL(gl_functions, "glGetShaderiv", log_tag)
        if(is_compiled == GL_FALSE) {
          GLint max_length = 0;
          gl_functions.glGetShaderiv(shader, GL_INFO_LOG_LENGTH,
            &max_length);
          GL_CALL(gl_functions, "glGetShaderiv", log_tag)

          std::vector<GLchar> error_log(
            static_cast<std::size_t>(max_length));
          gl_functions.glGetShaderInfoLog(shader, max_length, &max_length,
            &error_log[0]);
          GL_CALL(gl_functions, "glGetShaderInfoLog", log_tag)

          std::string log(error_log.begin(), error_log.end());
          logging::error(log_tag, log);

          gl_functions.glDeleteShader(shader);
          GL_CALL(gl_functions, "glDeleteShader", log_tag)

          ret = false;
        }

        return ret;
      }

      bool check_if_shader_program_linked(GLuint program,
        QOpenGLFunctions &gl_functions, const std::string &log_tag)
      {
        bool ret = true;

        GLint is_linked = 0;
        gl_functions.glGetProgramiv(program, GL_LINK_STATUS, &is_linked);
        GL_CALL(gl_functions, "glGetProgramiv", log_tag)

        if(is_linked == GL_FALSE) {
          GLint max_length = 0;
          gl_functions.glGetProgramiv(program, GL_INFO_LOG_LENGTH,
            &max_length);
          GL_CALL(gl_functions, "glGetProgramiv", log_tag)

          std::vector<GLchar> info_log(static_cast<std::size_t>(max_length));
          gl_functions.glGetProgramInfoLog(program, max_length, &max_length,
            &info_log[0]);
          GL_CALL(gl_functions, "glGetProgramInfoLog", log_tag)
          gl_functions.glDeleteProgram(program);
          GL_CALL(gl_functions, "glDeleteProgram", log_tag)

          ret = false;
        }

        return ret;
      }
    }

    glsl_shader_program::glsl_shader_program() :
      shader_program_(0),
      vertex_shader_(0),
      fragment_shader_(0),
      log_tag_(logging::log_tag_for_this(*this))
    {
      logging::add_std_log_logger(logging::log_tag_for_this(*this), INFO);
    }

    glsl_shader_program::~glsl_shader_program()
    {}

    void glsl_shader_program::add_vertex_shader_source(
      const std::string &src)
    {
      vertex_shader_sources_.push_back(src);
    }

    void glsl_shader_program::add_vertex_shader_sources(
      const std::vector<std::string> &src)
    {
      std::copy(src.begin(), src.end(),
        std::back_inserter(vertex_shader_sources_));
    }

    void glsl_shader_program::add_fragment_shader_source(
      const std::string &src)
    {
      fragment_shader_sources_.push_back(src);
    }

    void glsl_shader_program::add_fragment_shader_sources(
      const std::vector<std::string> &src)
    {
      std::copy(src.begin(), src.end(),
        std::back_inserter(fragment_shader_sources_));
    }

    bool glsl_shader_program::create_program(QOpenGLFunctions &gl_functions)
    {
      bool ret = true;

      if (ret) {
        detail::compile_shader(vertex_shader_, gl_functions,
          GL_VERTEX_SHADER, vertex_shader_sources_, log_tag_);
      }

      ret = (ret && detail::check_if_shader_compiled(vertex_shader_,
        gl_functions, log_tag_));

      if (ret) {
        detail::compile_shader(fragment_shader_, gl_functions,
          GL_FRAGMENT_SHADER, fragment_shader_sources_, log_tag_);
      }

      ret = (ret && detail::check_if_shader_compiled(fragment_shader_,
        gl_functions, log_tag_));

      if (ret) {
        shader_program_ = gl_functions.glCreateProgram();
        GL_CALL(gl_functions, "glCreateProgram", log_tag_)

        gl_functions.glAttachShader(shader_program_, vertex_shader_);
        GL_CALL(gl_functions, "glAttachShader", log_tag_)

        gl_functions.glAttachShader(shader_program_, fragment_shader_);
        GL_CALL(gl_functions, "glAttachShader", log_tag_)

        gl_functions.glLinkProgram(shader_program_);
        GL_CALL(gl_functions, "glLinkProgram", log_tag_)
      }

      ret = (ret && detail::check_if_shader_program_linked(shader_program_,
        gl_functions, log_tag_));

      if (!ret) {
        gl_functions.glDeleteShader(vertex_shader_);
        GL_CALL(gl_functions, "glDeleteShader", log_tag_)
        gl_functions.glDeleteShader(fragment_shader_);
        GL_CALL(gl_functions, "glDeleteShader", log_tag_)
      } else {
        gl_functions.glDetachShader(shader_program_, vertex_shader_);
        GL_CALL(gl_functions, "glDetachShader", log_tag_)
        gl_functions.glDetachShader(shader_program_, fragment_shader_);
        GL_CALL(gl_functions, "glDetachShader", log_tag_)
      }

      return ret;
    }

    GLuint glsl_shader_program::id() const
    {
      return shader_program_;
    }

    GLuint glsl_shader_program::vertex_shader_id() const
    {
      return vertex_shader_;
    }

    GLuint glsl_shader_program::fragment_shader_id() const
    {
      return fragment_shader_;
    }
  }
}
