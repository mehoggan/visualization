#ifndef COM_VISUALIZATION_SCENES_INDX_TEX_RAINBOW_RECTANGLE_H_INCLUDED
#define COM_VISUALIZATION_SCENES_INDX_TEX_RAINBOW_RECTANGLE_H_INCLUDED

#include "declspec.h"

#include "com/visualization/scene.h"
#include "com/visualization/glsl_shader_program.h"

#include "opengl_graphics/mesh_types/interleaved_data.h"
#include "opengl_graphics/mesh_types/indices.h"
#include "opengl_math/primitives/points/type_point_2d.h"
#include "opengl_math/primitives/colors/type_color_rgb.h"
#include "opengl_math/primitives/texcoords/type_texcoord_2d.h"

#include <QOpenGLShaderProgram>

#include <atomic>

#ifdef __APPLE__
  #include <OpenGL/gl.h>
#elif __linux__
  #include <GL/gl.h>
#endif

namespace com
{
  namespace visualization
  {
    class DLLSPEC_COM_VISUALIZATION indexed_rainbow_textured_rectangle :
      public scene
    {
    public:
      indexed_rainbow_textured_rectangle();
      virtual ~indexed_rainbow_textured_rectangle();

      virtual bool initialize(QOpenGLFunctions &gl_functions);

      virtual void resize(int parent_width, int parent_height,
        float retina_scale);
      virtual void pre_draw(QOpenGLFunctions &gl_functions);
      virtual void draw(QOpenGLFunctions &gl_functions);
      virtual void post_draw(QOpenGLFunctions &gl_functions);

      virtual bool de_initialize(QOpenGLFunctions &gl_functions);

    private:
      int width_;
      int height_;
      float retina_scale_;

      glsl_shader_program shader_program_;
      GLuint vbo_;
      GLuint ebo_;
      GLuint tex_;

      typedef opengl_graphics::interleaved_data<opengl_math::point_2d<float>,
        opengl_math::color_rgb<float>,
        opengl_math::texcoord_2d<float>> vbo_type;
      vbo_type vbo_data_;
      const std::size_t total_verts_ = 4u;

      typedef opengl_graphics::indices<uint32_t> ebo_type;
      ebo_type ebo_data_;
      const std::size_t total_elements_ = 6u;

      std::atomic<bool> initialized_;
    };
  }
}
#endif
