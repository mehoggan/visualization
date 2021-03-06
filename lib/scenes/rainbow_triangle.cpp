#include "com/visualization/scenes/rainbow_triangle.h"

#include "com/visualization/gl_helpers.h"

#include "opengl_graphics/mesh_types/datums/interleaved_datum_2d.h"

namespace com
{
  namespace visualization
  {
    const char *rainbow_vertex_source =
      "attribute vec2 position;\n"
      "attribute vec3 color;\n"
      "varying vec3 Color;\n"
      "void main()\n"
      "{\n"
        "Color = color;\n"
        "gl_Position = vec4(position, 0.0, 1.0);\n"
      "}";

    const char *rainbow_fragment_source =
      "varying vec3 Color;\n"
      "void main()\n"
      "{\n"
      "  gl_FragColor = vec4(Color, 1.0);\n"
      "}";

    // Shader sources
    rainbow_triangle::rainbow_triangle() :
      width_(0),
      height_(0),
      retina_scale_(1.0),
      vbo_(0),
      initialized_(false)
    {
      logging::add_std_log_logger(logging::log_tag_for_this(*this), INFO);
    }

    rainbow_triangle::~rainbow_triangle()
    {}

    bool rainbow_triangle::initialize(QOpenGLFunctions &gl_functions)
    {
      if (!initialized_.load()) {
        std::string log_tag = logging::log_tag_for_this(*this);

        shader_program_.add_vertex_shader_source(rainbow_vertex_source);
        shader_program_.add_fragment_shader_source(rainbow_fragment_source);

        if (!shader_program_.create_program(gl_functions)) {
          logging::fatal(log_tag, "Failed to create program for\n",
            rainbow_vertex_source, "\n\n and \n\n", rainbow_fragment_source);
          throw std::runtime_error("Failed to create program");
        }

        gl_functions.glGenBuffers(1, &vbo_);
        GL_CALL(gl_functions, "glGenBuffers", log_tag);
        gl_functions.glBindBuffer(GL_ARRAY_BUFFER, vbo_);
        GL_CALL(gl_functions, "glBindBuffer", log_tag);

        vbo_type::collection_type data(
          new vbo_type::datum_type[total_verts_]);
        data[0] = vbo_type::datum_type(
          opengl_math::point_2d<float>(+0.0f, +0.5f),
          opengl_math::color_rgb<float>(+1.0f, +0.0f, +0.0f));
        data[1] = vbo_type::datum_type(
          opengl_math::point_2d<float>(+0.5f, -0.5f),
          opengl_math::color_rgb<float>(+0.0f, +1.0f, +0.0f));
        data[2] = vbo_type::datum_type(
          opengl_math::point_2d<float>(-0.5f, -0.5f),
          opengl_math::color_rgb<float>(+0.0f, +0.0f, +1.0f));
        vbo_data_ = vbo_type(data, total_verts_);
        std::size_t byte_count = vbo_data_.get_byte_count();
        gl_functions.glBufferData(GL_ARRAY_BUFFER, byte_count,
          vbo_data_.get_data().get(), GL_STATIC_DRAW);
        GL_CALL(gl_functions, "glBufferData", log_tag);

        initialized_.store(true);
      }

      return initialized_.load();
    }

    void rainbow_triangle::resize(int parent_width, int parent_height,
      float retina_scale)
    {
      width_ = static_cast<int>(1.0 * parent_width);
      height_ = static_cast<int>(1.0 * parent_height);
      retina_scale_ = retina_scale;
    }

    void rainbow_triangle::pre_draw(QOpenGLFunctions &gl_functions)
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
      gl_functions.glVertexAttribPointer(pos_attrib,
        vbo_type::datum_type::internal_type1::dimension, GL_FLOAT, GL_FALSE,
        vbo_type::traits::stride, (void *)vbo_type::traits::type1_byte_offset);
      GL_CALL(gl_functions, "glVertexAttribPointer", log_tag);

      GLint col_attrib = gl_functions.glGetAttribLocation(
        shader_program_.id(), "color");
      GL_CALL(gl_functions, "glGetAttribLocation", log_tag);
      gl_functions.glEnableVertexAttribArray(col_attrib);
      GL_CALL(gl_functions, "glEnableVertexAttribArray", log_tag);
      gl_functions.glVertexAttribPointer(col_attrib,
        vbo_type::datum_type::internal_type2::dimension, GL_FLOAT, GL_FALSE,
        vbo_type::traits::stride, (void *)vbo_type::traits::type2_byte_offset);
      GL_CALL(gl_functions, "glVertexAttribPointer", log_tag);
    }

    void rainbow_triangle::draw(QOpenGLFunctions &gl_functions)
    {
      std::string log_tag = logging::log_tag_for_this(*this);

      gl_functions.glDrawArrays(GL_TRIANGLES, 0, total_verts_);
      GL_CALL(gl_functions, "glDrawArrays", log_tag);
    }

    void rainbow_triangle::post_draw(QOpenGLFunctions &gl_functions)
    {
      std::string log_tag = logging::log_tag_for_this(*this);

      GLint col_attrib = gl_functions.glGetAttribLocation(
        shader_program_.id(), "color");
      GL_CALL(gl_functions, "glGetAttribLocation", log_tag);
      gl_functions.glDisableVertexAttribArray(col_attrib);
      GL_CALL(gl_functions, "glDisableVertexAttribArray", log_tag);

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

    bool rainbow_triangle::de_initialize(QOpenGLFunctions &gl_functions)
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
