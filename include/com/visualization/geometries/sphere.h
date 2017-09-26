#ifndef COM_VISUALIZATION_GEOMETRIES_SPHERE_H_INCLUDED
#define COM_VISUALIZATION_GEOMETRIES_SPHERE_H_INCLUDED

#include "declspec.h"

#include "com/visualization/geometry.h"

#include "com/visualization/glsl_shader_program.h"

#include "opengl_graphics/mesh_types/interleaved_data.h"
#include "opengl_graphics/mesh_types/indices.h"
#include "opengl_math/primitives/points/type_point_3d.h"
#include "opengl_math/primitives/colors/type_color_rgb.h"
#include "opengl_math/primitives/vectors/type_vector_3d.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <QOpenGLShaderProgram>

#include <atomic>
#include <tuple>

#ifdef __APPLE__
  #include <OpenGL/gl.h>
#elif __linux__
  #include <GL/gl.h>
#endif

namespace com
{
  namespace visualization
  {
    class DLLSPEC_COM_VISUALIZATION sphere :
      public geometry
    {
    public:
      explicit sphere(float radius = 1.0f);
      virtual ~sphere();

      virtual bool initialize(QOpenGLFunctions &gl_functions);

      virtual void resize(int parent_width, int parent_height,
        float retina_scale);
      virtual void pre_draw(QOpenGLFunctions &gl_functions);
      virtual void draw(QOpenGLFunctions &gl_functions);
      virtual void post_draw(QOpenGLFunctions &gl_functions);

      virtual bool de_initialize(QOpenGLFunctions &gl_functions);

      virtual glm::mat4 compute_and_set_mvp_matrix(
        QOpenGLFunctions gl_functions,
        glm::mat4 &proj_matrix, glm::mat4 &view_matrix);

    private:
      typedef opengl_graphics::interleaved_data<
        opengl_math::point_3d<float>,
        opengl_math::color_rgb<float>
      > vbo_type;
      typedef opengl_graphics::indices<uint32_t> ebo_type;

      std::tuple<
        vbo_type::collection_type,
        std::size_t,
        ebo_type::collection_type,
        std::size_t
      > generate();

    private:
      int width_;
      int height_;
      float retina_scale_;
      glsl_shader_program shader_program_;
      GLuint vbo_;
      GLuint ebo_;

      glm::mat4 model_;

      vbo_type vbo_data_;
      ebo_type ebo_data_;

      float radius_;

      std::string log_tag_;

      std::atomic<bool> initialized_;
    };
  }
}

#endif
