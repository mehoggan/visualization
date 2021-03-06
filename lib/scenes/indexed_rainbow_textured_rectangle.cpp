#include "com/visualization/scenes/indexed_rainbow_textured_rectangle.h"

#include "com/visualization/application.h"
#include "com/visualization/gl_helpers.h"

#include "opengl_graphics/mesh_types/datums/interleaved_datum_2d.h"

#include <SOIL.h>

namespace com
{
  namespace visualization
  {
    const char *indexed_rainbow_textured_rectangle_vertex_source =
      "attribute vec2 position;\n"
      "attribute vec3 color;\n"
      "attribute vec2 texcoord;\n"
      "varying vec3 Color;\n"
      "varying vec2 Texcoord;\n"
      "void main()\n"
      "{\n"
        "Color = color;\n"
        "Texcoord = texcoord;\n"
        "gl_Position = vec4(position, 0.0, 1.0);\n"
      "}";

    const char *indexed_rainbow_textured_rectangle_fragment_source =
      "varying vec3 Color;\n"
      "varying vec2 Texcoord;\n"
      "uniform sampler2D tex;\n"
      "void main()\n"
      "{\n"
      "  gl_FragColor = texture2D(tex, Texcoord) * vec4(Color, 1.0);\n"
      "}";

    // Shader sources
    indexed_rainbow_textured_rectangle::
      indexed_rainbow_textured_rectangle() :
      width_(0),
      height_(0),
      retina_scale_(1.0),
      vbo_(0),
      initialized_(false)
    {
      logging::add_std_log_logger(logging::log_tag_for_this(*this), INFO);
    }

    indexed_rainbow_textured_rectangle::~indexed_rainbow_textured_rectangle()
    {}

    bool indexed_rainbow_textured_rectangle::initialize(
      QOpenGLFunctions &gl_functions)
    {
      if (!initialized_.load()) {
        std::string log_tag = logging::log_tag_for_this(*this);

        shader_program_.add_vertex_shader_source(
          indexed_rainbow_textured_rectangle_vertex_source);
        shader_program_.add_fragment_shader_source(
          indexed_rainbow_textured_rectangle_fragment_source);

        if (!shader_program_.create_program(gl_functions)) {
          logging::fatal(log_tag, "Failed to create program for\n",
            indexed_rainbow_textured_rectangle_vertex_source, "\n\n and \n\n",
            indexed_rainbow_textured_rectangle_fragment_source);
          throw std::runtime_error("Failed to create program");
        }

        gl_functions.glGenBuffers(1, &vbo_);
        GL_CALL(gl_functions, "glGenBuffers", log_tag);
        gl_functions.glBindBuffer(GL_ARRAY_BUFFER, vbo_);
        GL_CALL(gl_functions, "glBindBuffer", log_tag);
        vbo_type::collection_type data(
          new vbo_type::datum_type[total_verts_]);
        data[0] = vbo_type::datum_type(
          opengl_math::point_2d<float>(-0.5f, +0.5f),
          opengl_math::color_rgb<float>(+1.0f, +0.0f, +0.0f),
          opengl_math::texcoord_2d<float>(0.0f, 0.0f));
        data[1] = vbo_type::datum_type(
          opengl_math::point_2d<float>(+0.5f, +0.5f),
          opengl_math::color_rgb<float>(+0.0f, +1.0f, +0.0f),
          opengl_math::texcoord_2d<float>(1.0f, 0.0f));
        data[2] = vbo_type::datum_type(
          opengl_math::point_2d<float>(+0.5f, -0.5f),
          opengl_math::color_rgb<float>(+0.0f, +0.0f, +1.0f),
          opengl_math::texcoord_2d<float>(1.0f, 1.0f));
        data[3] = vbo_type::datum_type(
          opengl_math::point_2d<float>(-0.5f, -0.5f),
          opengl_math::color_rgb<float>(+1.0f, +1.0f, +1.0f),
          opengl_math::texcoord_2d<float>(0.0f, 1.0f));
        vbo_data_ = vbo_type(data, total_verts_);
        std::size_t byte_count = vbo_data_.get_byte_count();
        gl_functions.glBufferData(GL_ARRAY_BUFFER, byte_count,
          vbo_data_.get_data().get(), GL_STATIC_DRAW);
        GL_CALL(gl_functions, "glBufferData", log_tag);
        gl_functions.glGenBuffers(1, &ebo_);
        GL_CALL(gl_functions, "glGenBuffers", log_tag);
        gl_functions.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
        GL_CALL(gl_functions, "glBindBuffer", log_tag);
        ebo_type::collection_type indic(new uint32_t[total_elements_]);
        indic[0] = 0u;
        indic[1] = 1u;
        indic[2] = 2u;
        indic[3] = 2u;
        indic[4] = 3u;
        indic[5] = 0u;
        ebo_data_ = ebo_type(indic, total_elements_);
        byte_count = ebo_data_.get_byte_count();
        gl_functions.glBufferData(GL_ELEMENT_ARRAY_BUFFER, byte_count,
          ebo_data_.get_data().get(), GL_STATIC_DRAW);
        GL_CALL(gl_functions, "glBufferData", log_tag);

        boost::filesystem::path image_path = application::exe_dir() /
          "sample.png";
        int width = 0;
        int  height = 0;
        logging::info(log_tag, "Loading image from:", image_path);
        unsigned char* image = SOIL_load_image(image_path.string().c_str(),
          &width, &height, 0, SOIL_LOAD_RGB);
        gl_functions.glGenTextures(1, &tex_);
        GL_CALL(gl_functions, "glGenTextures", log_tag);
        gl_functions.glBindTexture(GL_TEXTURE_2D, tex_);
        GL_CALL(gl_functions, "glBindTexture", log_tag);
        gl_functions.glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
          GL_RGB, GL_UNSIGNED_BYTE, image);
        GL_CALL(gl_functions, "glTexImage2D", log_tag);
        SOIL_free_image_data(image);

        gl_functions.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
          GL_CLAMP_TO_EDGE);
        GL_CALL(gl_functions, "glTexParameteri", log_tag);
        gl_functions.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
          GL_CLAMP_TO_EDGE);
        GL_CALL(gl_functions, "glTexParameteri", log_tag);
        gl_functions.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
          GL_LINEAR);
        GL_CALL(gl_functions, "glTexParameteri", log_tag);
        gl_functions.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
          GL_LINEAR);
        GL_CALL(gl_functions, "glTexParameteri", log_tag);

        initialized_.store(true);
      }

      return initialized_.load();
    }

    void indexed_rainbow_textured_rectangle::resize(int parent_width,
      int parent_height, float retina_scale)
    {
      width_ = static_cast<int>(1.0 * parent_width);
      height_ = static_cast<int>(1.0 * parent_height);
      retina_scale_ = retina_scale;
    }

    void indexed_rainbow_textured_rectangle::pre_draw(
      QOpenGLFunctions &gl_functions)
    {
      std::string log_tag = logging::log_tag_for_this(*this);

      gl_functions.glBindTexture(GL_TEXTURE_2D, tex_);
      GL_CALL(gl_functions, "glBindTexture", log_tag);

      gl_functions.glBindBuffer(GL_ARRAY_BUFFER, vbo_);
      GL_CALL(gl_functions, "glBindBuffer", log_tag);

      gl_functions.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
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
        vbo_type::traits::stride,
        (void *)vbo_type::traits::type1_byte_offset);
      GL_CALL(gl_functions, "glVertexAttribPointer", log_tag);

      GLint col_attrib = gl_functions.glGetAttribLocation(
        shader_program_.id(), "color");
      GL_CALL(gl_functions, "glGetAttribLocation", log_tag);
      gl_functions.glEnableVertexAttribArray(col_attrib);
      GL_CALL(gl_functions, "glEnableVertexAttribArray", log_tag);
      gl_functions.glVertexAttribPointer(col_attrib,
        vbo_type::datum_type::internal_type2::dimension, GL_FLOAT, GL_FALSE,
        vbo_type::traits::stride,
        (void*)vbo_type::traits::type2_byte_offset);
      GL_CALL(gl_functions, "glVertexAttribPointer", log_tag);

      GLint tex_attrib = gl_functions.glGetAttribLocation(
        shader_program_.id(), "texcoord");
      GL_CALL(gl_functions, "glGetAttribLocation", log_tag);
      gl_functions.glEnableVertexAttribArray(tex_attrib);
      GL_CALL(gl_functions, "glEnableVertexAttribArray", log_tag);
      gl_functions.glVertexAttribPointer(tex_attrib,
        vbo_type::datum_type::internal_type3::dimension, GL_FLOAT, GL_FALSE,
        vbo_type::traits::stride,
        (void*)vbo_type::traits::type3_byte_offset);
      GL_CALL(gl_functions, "glVertexAttribPointer", log_tag);
    }

    void indexed_rainbow_textured_rectangle::draw(
      QOpenGLFunctions &gl_functions)
    {
      std::string log_tag = logging::log_tag_for_this(*this);

      // Draw a rectangle from the 2 triangles using 6 indices
      glDrawElements(GL_TRIANGLES, (GLsizei)ebo_data_.get_indices_count(),
        GL_UNSIGNED_INT, 0);
      GL_CALL(gl_functions, "glDrawElements", log_tag);
    }

    void indexed_rainbow_textured_rectangle::post_draw(
      QOpenGLFunctions &gl_functions)
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

      gl_functions.glBindTexture(GL_TEXTURE_2D, 0);
      GL_CALL(gl_functions, "glBindTexture", log_tag);

      gl_functions.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
      GL_CALL(gl_functions, "glBindBuffer", log_tag);

      gl_functions.glBindBuffer(GL_ARRAY_BUFFER, 0);
      GL_CALL(gl_functions, "glBindBuffer", log_tag);

      gl_functions.glUseProgram(0);
      GL_CALL(gl_functions, "glUseProgram", log_tag);
      gl_functions.glBindBuffer(GL_ARRAY_BUFFER, 0);
      GL_CALL(gl_functions, "glBindBuffer", log_tag);
    }

    bool indexed_rainbow_textured_rectangle::de_initialize(
      QOpenGLFunctions &gl_functions)
    {
      std::string log_tag = logging::log_tag_for_this(*this);

      logging::info(log_tag, "Going to delete resources...");

      gl_functions.glDeleteTextures(1, &tex_);
      GL_CALL(gl_functions, "glDeleteTextures", log_tag);
      gl_functions.glDeleteProgram(shader_program_.id());
      GL_CALL(gl_functions, "glDeleteProgram", log_tag);
      gl_functions.glDeleteShader(shader_program_.fragment_shader_id());
      GL_CALL(gl_functions, "glDeleteShader", log_tag);
      gl_functions.glDeleteShader(shader_program_.vertex_shader_id());
      GL_CALL(gl_functions, "glDeleteShader", log_tag);
      gl_functions.glDeleteBuffers(1, &ebo_);
      GL_CALL(gl_functions, "glDeleteBuffers", log_tag);
      gl_functions.glDeleteBuffers(1, &vbo_);
      GL_CALL(gl_functions, "glDeleteBuffers", log_tag);

      return true;
    }
  }
}
