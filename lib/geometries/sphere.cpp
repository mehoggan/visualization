#include "com/visualization/geometries/sphere.h"

#include "com/visualization/gl_helpers.h"
#include "com/visualization/logging.h"

#include "opengl_graphics/mesh_types/datums/interleaved_datum_2d.h"

namespace com
{
  namespace visualization
  {
    const char *sphere_vertex_source =
      "attribute vec3 position;\n"
      "attribute vec3 color;\n"
      "varying vec3 Color;\n"
      "uniform mat4 mvp;\n"
      "void main()\n"
      "{\n"
        "Color = color;\n"
        "gl_Position = mvp * vec4(position, 1.0);\n"
      "}";

    const char *sphere_fragment_source =
      "varying vec3 Color;\n"
      "void main()\n"
      "{\n"
      "  gl_FragColor = vec4(Color, 1.0);\n"
      "}";

    sphere::sphere() :
      width_(0),
      height_(0),
      retina_scale_(1.0),
      vbo_(0),
      ebo_(0),
      model_(1.0f),
      log_tag_(logging::log_tag_for_this(*this)),
      initialized_(false)
    {
      logging::add_std_log_logger(logging::log_tag_for_this(*this), INFO);
    }

    sphere::~sphere()
    {}

    std::pair<
      sphere::vbo_type::collection_type,
      sphere::ebo_type::collection_type
    > sphere::generate()
    {
      sphere::vbo_type::collection_type data(
        new vbo_type::datum_type[total_verts_]);
      data[0] = vbo_type::datum_type(
        opengl_math::point_3d<float>(-0.5f, +0.5f, +0.5f),
        opengl_math::color_rgb<float>(+1.0f, +0.0f, +0.0f));
      data[1] = vbo_type::datum_type(
        opengl_math::point_3d<float>(+0.5f, +0.5f, +0.5f),
        opengl_math::color_rgb<float>(+0.0f, +1.0f, +0.0f));
      data[2] = vbo_type::datum_type(
        opengl_math::point_3d<float>(+0.5f, -0.5f, +0.5f),
        opengl_math::color_rgb<float>(+0.0f, +0.0f, +1.0f));
      data[3] = vbo_type::datum_type(
        opengl_math::point_3d<float>(-0.5f, -0.5f, +0.5f),
        opengl_math::color_rgb<float>(+1.0f, +1.0f, +1.0f));

      ebo_type::collection_type indic(new uint32_t[total_elements_]);
      indic[0] = 0u;
      indic[1] = 1u;
      indic[2] = 2u;
      indic[3] = 2u;
      indic[4] = 3u;
      indic[5] = 0u;

      return std::make_pair(data, indic);
    }

    bool sphere::initialize(QOpenGLFunctions &gl_functions)
    {
      if (!initialized_.load()) {
        shader_program_.add_vertex_shader_source(sphere_vertex_source);
        shader_program_.add_fragment_shader_source(sphere_fragment_source);

        if (!shader_program_.create_program(gl_functions)) {
          logging::fatal(log_tag_,"Failed to create program for\n",
            sphere_vertex_source, "\n\n and \n\n", sphere_fragment_source);
          throw std::runtime_error("Failed to create program");
        }

        std::pair<
          sphere::vbo_type::collection_type,
          sphere::ebo_type::collection_type
        > sphere_data = generate();

        gl_functions.glGenBuffers(1, &vbo_);
        GL_CALL(gl_functions, "glGenBuffers", log_tag_);
        gl_functions.glBindBuffer(GL_ARRAY_BUFFER, vbo_);
        GL_CALL(gl_functions, "glBindBuffer", log_tag_);
        vbo_data_ = vbo_type(sphere_data.first, total_verts_);
        std::size_t byte_count = vbo_data_.get_byte_count();
        gl_functions.glBufferData(GL_ARRAY_BUFFER, byte_count,
          vbo_data_.get_data().get(), GL_STATIC_DRAW);

        GL_CALL(gl_functions, "glBufferData", log_tag_);
        gl_functions.glGenBuffers(1, &ebo_);
        GL_CALL(gl_functions, "glGenBuffers", log_tag_);
        gl_functions.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
        GL_CALL(gl_functions, "glBindBuffer", log_tag_);
        ebo_data_ = ebo_type(sphere_data.second, total_elements_);
        byte_count = ebo_data_.get_byte_count();
        gl_functions.glBufferData(GL_ELEMENT_ARRAY_BUFFER, byte_count,
          ebo_data_.get_data().get(), GL_STATIC_DRAW);
        GL_CALL(gl_functions, "glBufferData", log_tag_);

        initialized_.store(true);
      }

      return initialized_.load();
    }

    void sphere::resize(int parent_width, int parent_height,
      float retina_scale)
    {
      width_ = parent_width;
      height_ = parent_height;
      retina_scale_ = retina_scale;
    }

    void sphere::pre_draw(QOpenGLFunctions &gl_functions)
    {
      gl_functions.glUseProgram(shader_program_.id());
      GL_CALL(gl_functions, "glUseProgram", log_tag_);

      gl_functions.glBindBuffer(GL_ARRAY_BUFFER, vbo_);
      GL_CALL(gl_functions, "glBindBuffer", log_tag_);

      gl_functions.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
      GL_CALL(gl_functions, "glBindBuffer", log_tag_);

      GLint pos_attrib = gl_functions.glGetAttribLocation(
        shader_program_.id(), "position");
      GL_CALL(gl_functions, "glGetAttribLocation", log_tag_);
      gl_functions.glEnableVertexAttribArray(pos_attrib);
      GL_CALL(gl_functions, "glEnableVertexAttribArray", log_tag_);
      gl_functions.glVertexAttribPointer(pos_attrib,
        vbo_type::datum_type::internal_type1::dimension, GL_FLOAT, GL_FALSE,
        vbo_type::traits::stride,
        (void *)vbo_type::traits::type1_byte_offset);
      GL_CALL(gl_functions, "glVertexAttribPointer", log_tag_);

      GLint col_attrib = gl_functions.glGetAttribLocation(
        shader_program_.id(), "color");
      GL_CALL(gl_functions, "glGetAttribLocation", log_tag_);
      gl_functions.glEnableVertexAttribArray(col_attrib);
      GL_CALL(gl_functions, "glEnableVertexAttribArray", log_tag_);
      gl_functions.glVertexAttribPointer(col_attrib,
        vbo_type::datum_type::internal_type2::dimension, GL_FLOAT, GL_FALSE,
        vbo_type::traits::stride,
        (void*)vbo_type::traits::type2_byte_offset);
      GL_CALL(gl_functions, "glVertexAttribPointer", log_tag_);
    }

    void sphere::draw(QOpenGLFunctions &gl_functions)
    {
      glDrawElements(GL_TRIANGLES, (GLsizei)ebo_data_.get_indices_count(),
        GL_UNSIGNED_INT, 0);
      GL_CALL(gl_functions, "glDrawElements", log_tag_);
    }

    void sphere::post_draw(QOpenGLFunctions &gl_functions)
    {
      GLint col_attrib = gl_functions.glGetAttribLocation(
        shader_program_.id(), "color");
      GL_CALL(gl_functions, "glGetAttribLocation", log_tag_);
      gl_functions.glDisableVertexAttribArray(col_attrib);
      GL_CALL(gl_functions, "glDisableVertexAttribArray", log_tag_);

      GLint pos_attrib = gl_functions.glGetAttribLocation(
        shader_program_.id(), "position");
      GL_CALL(gl_functions, "glGetAttribLocation", log_tag_);
      gl_functions.glDisableVertexAttribArray(pos_attrib);
      GL_CALL(gl_functions, "glDisableVertexAttribArray", log_tag_);

      gl_functions.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
      GL_CALL(gl_functions, "glBindBuffer", log_tag_);

      gl_functions.glBindBuffer(GL_ARRAY_BUFFER, 0);
      GL_CALL(gl_functions, "glBindBuffer", log_tag_);

      gl_functions.glUseProgram(0);
      GL_CALL(gl_functions, "glUseProgram", log_tag_);
      gl_functions.glBindBuffer(GL_ARRAY_BUFFER, 0);
      GL_CALL(gl_functions, "glBindBuffer", log_tag_);
    }

    bool sphere::de_initialize(
      QOpenGLFunctions &gl_functions)
    {
      logging::info(log_tag_, "Going to delete resources...");

      gl_functions.glDeleteProgram(shader_program_.id());
      GL_CALL(gl_functions, "glDeleteProgram", log_tag_);
      gl_functions.glDeleteShader(shader_program_.fragment_shader_id());
      GL_CALL(gl_functions, "glDeleteShader", log_tag_);
      gl_functions.glDeleteShader(shader_program_.vertex_shader_id());
      GL_CALL(gl_functions, "glDeleteShader", log_tag_);
      gl_functions.glDeleteBuffers(1, &ebo_);
      GL_CALL(gl_functions, "glDeleteBuffers", log_tag_);
      gl_functions.glDeleteBuffers(1, &vbo_);
      GL_CALL(gl_functions, "glDeleteBuffers", log_tag_);

      return true;
    }


    glm::mat4 sphere::compute_and_set_mvp_matrix(
      QOpenGLFunctions gl_functions, glm::mat4 &proj, glm::mat4 &view)
    {
      glm::mat4 mvp = proj * view * model_;

      GLint uni_mvp = gl_functions.glGetUniformLocation(
        shader_program_.id(), "mvp");
      GL_CALL(gl_functions, "glGetUniformLocation", log_tag_);
      gl_functions.glUniformMatrix4fv(uni_mvp, 1, GL_FALSE,
        glm::value_ptr(mvp));
      GL_CALL(gl_functions, "glUniformMatrix4fv", log_tag_);

      return proj * view * model_;
    }
  }
}