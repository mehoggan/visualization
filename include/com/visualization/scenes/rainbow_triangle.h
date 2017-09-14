#ifndef COM_VISUALIZATION_SCENES_RAINBOW_TRIANGLE_H_INCLUDED
#define COM_VISUALIZATION_SCENES_RAINBOW_TRIANGLE_H_INCLUDED

#include "declspec.h"

#include "com/visualization/scene.h"
#include "com/visualization/glsl_shader_program.h"

#include "opengl_graphics/mesh_types/interleaved_data.h"
#include "opengl_math/primitives/points/type_point_2d.h"
#include "opengl_math/primitives/colors/type_color_rgb.h"

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
    class DLLSPEC_COM_VISUALIZATION rainbow_triangle :
      public scene
    {
    public:
      rainbow_triangle();
      virtual ~rainbow_triangle();

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

      typedef opengl_graphics::interleaved_data<opengl_math::point_2d<float>,
        opengl_math::color_rgb<float>> vbo_type;
      vbo_type vbo_data_;
      const std::size_t total_verts_ = 3u;

      std::atomic<bool> initialized_;
    };
  }
}

#endif
