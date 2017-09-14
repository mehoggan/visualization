#include "com/visualization/scenes/simple_triangle.h"

#include "com/visualization/gl_helpers.h"

namespace com
{
  namespace visualization
  {
    // Shader sources
    const GLchar* vertex_source =
      "attribute vec2 position;\n"
      "void main()\n"
      "{\n"
        "gl_Position = vec4(position, 0.0, 1.0);\n"
      "}\n";

    const GLchar* fragment_source =
      "void main()\n"
      "{\n"
        "gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);\n"
      "}\n";

    simple_triangle::simple_triangle() :
      width_(0),
      height_(0),
      retina_scale_(1.0),
      vbo_(0),
      initialized_(false)
    {
      logging::add_std_log_logger(logging::log_tag_for_this(*this), INFO);
    }

    simple_triangle::~simple_triangle()
    {}

    bool simple_triangle::initialize(QOpenGLFunctions &gl_functions)
    {
      if (!initialized_.load()) {
        std::string log_tag = logging::log_tag_for_this(*this);

        shader_program_.add_vertex_shader_source(vertex_source);
        shader_program_.add_fragment_shader_source(fragment_source);

        if (!shader_program_.create_program(gl_functions)) {
          logging::fatal(log_tag, "Failed to create program for\n",
            vertex_source, "\n\n and \n\n", fragment_source);
          throw std::runtime_error("Failed to create program");
        }

        gl_functions.glGenBuffers(1, &vbo_);
        GL_CALL(gl_functions, "glGenBuffers", log_tag);
        gl_functions.glBindBuffer(GL_ARRAY_BUFFER, vbo_);
        GL_CALL(gl_functions, "glBindBuffer", log_tag);

        vbo_type::collection1_type data(new vbo_type::type1[vert_count]);
        data[0] = vbo_type::type1(+0.0f, +0.5f);
        data[1] = vbo_type::type1(+0.5f, -0.5f);
        data[2] = vbo_type::type1(-0.5f, -0.5f);
        vbo_data_ = vbo_type(data, vert_count);
        const std::size_t byte_count1 = vbo_data_.get_bytecount_1();
        gl_functions.glBufferData(GL_ARRAY_BUFFER, byte_count1,
          vbo_data_.get_data1().get(), GL_STATIC_DRAW);
        GL_CALL(gl_functions, "glBufferData", log_tag);

        initialized_.store(true);
      }

      return initialized_.load();
    }

    void simple_triangle::resize(int parent_width, int parent_height,
      float retina_scale)
    {
      width_ = static_cast<int>(1.0 * parent_width);
      height_ = static_cast<int>(1.0 * parent_height);
      retina_scale_ = retina_scale;
    }

    void simple_triangle::pre_draw(QOpenGLFunctions &gl_functions)
    {
      std::string log_tag = logging::log_tag_for_this(*this);

      gl_functions.glBindBuffer(GL_ARRAY_BUFFER, vbo_);
      GL_CALL(gl_functions, "glBindBuffer", log_tag);
      gl_functions.glUseProgram(shader_program_.id());
      GL_CALL(gl_functions, "glUseProgram", log_tag);
      GLint pos_attrib = gl_functions.glGetAttribLocation(
        shader_program_.id(), "position");
      GL_CALL(gl_functions, "glGetAttribLocation", log_tag);
      gl_functions.glEnableVertexAttribArray(pos_attrib);
      GL_CALL(gl_functions, "glEnableVertexAttribArray", log_tag);
      gl_functions.glVertexAttribPointer(pos_attrib, 2, GL_FLOAT, GL_FALSE,
        0, 0);
      GL_CALL(gl_functions, "glVertexAttribPointer", log_tag);
    }

    void simple_triangle::draw(QOpenGLFunctions &gl_functions)
    {
      std::string log_tag = logging::log_tag_for_this(*this);

      glDrawArrays(GL_TRIANGLES, 0, vert_count);
      GL_CALL(gl_functions, "glDrawArrays", log_tag);
    }

    void simple_triangle::post_draw(QOpenGLFunctions &gl_functions)
    {
      std::string log_tag = logging::log_tag_for_this(*this);

      GLint pos_attrib = gl_functions.glGetAttribLocation(
        shader_program_.id(), "position");
      GL_CALL(gl_functions, "glGetAttribLocation", log_tag);
      gl_functions.glDisableVertexAttribArray(pos_attrib);
      GL_CALL(gl_functions, "glDisableVertexAttribArray", log_tag);
      gl_functions.glUseProgram(0);
      GL_CALL(gl_functions, "glUseProgram", log_tag);
      gl_functions.glBindBuffer(GL_ARRAY_BUFFER, 0);
      GL_CALL(gl_functions, "glBindBuffer", log_tag);
    }

    bool simple_triangle::de_initialize(QOpenGLFunctions &gl_functions)
    {
      std::string log_tag = logging::log_tag_for_this(*this);

      logging::info(log_tag, "Going to delete resources...");

      gl_functions.glDeleteProgram(shader_program_.id());
      GL_CALL(gl_functions, "glDeleteProgram", log_tag);
      gl_functions.glDeleteShader(shader_program_.fragment_shader_id());
      GL_CALL(gl_functions, "glDeleteShader", log_tag);
      gl_functions.glDeleteShader(shader_program_.vertex_shader_id());
      GL_CALL(gl_functions, "glDeleteShader", log_tag);
      gl_functions.glDeleteBuffers(1, &vbo_);
      GL_CALL(gl_functions, "glDeleteBuffers", log_tag);

      return true;
    }
  }
}
