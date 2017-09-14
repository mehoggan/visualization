#ifndef COM_VISUALIZATION_SCENES_INDEXED_RAINBOW_SPHERE_H_INCLUDED
#define COM_VISUALIZATION_SCENES_INDEXED_RAINBOW_SPHERE_H_INCLUDED

#include "declspec.h"

#include "com/visualization/geometry.h"
#include "com/visualization/scene.h"
#include "com/visualization/glsl_shader_program.h"

#include "opengl_graphics/mesh_types/interleaved_data.h"
#include "opengl_graphics/mesh_types/indices.h"
#include "opengl_math/primitives/points/type_point_3d.h"
#include "opengl_math/primitives/colors/type_color_rgb.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <QOpenGLShaderProgram>

#include <atomic>
#include <memory>
#include <string>

#ifdef __APPLE__
  #include <OpenGL/gl.h>
#elif __linux__
  #include <GL/gl.h>
#endif

namespace com
{
  namespace visualization
  {
    class DLLSPEC_COM_VISUALIZATION indexed_rainbow_sphere :
      public scene
    {
    public:
      indexed_rainbow_sphere();
      virtual ~indexed_rainbow_sphere();

      virtual bool initialize(QOpenGLFunctions &gl_functions) override;

      virtual void resize(int parent_width, int parent_height,
        float retina_scale) override;
      virtual void pre_draw(QOpenGLFunctions &gl_functions) override;
      virtual void draw(QOpenGLFunctions &gl_functions) override;
      virtual void post_draw(QOpenGLFunctions &gl_functions) override;

      virtual bool de_initialize(QOpenGLFunctions &gl_functions) override;

      virtual void wheel_event(std::int32_t x_delta, std::int32_t y_delta,
        std::uint32_t mouse_buttons, std::int32_t global_x,
        std::int32_t global_y, float global_xf, float global_yf,
        scroll_phase phase, std::int32_t pixel_delta_x,
        std::int32_t pixel_delta_y, std::int32_t x, std::int32_t y,
        float xf, float yf) override;

      virtual void key_press_event(int key_press_count,
        bool is_auto_repeat, std::uint32_t keyboard_modifiers,
        const char *key_sym, int key_val) override;

    private:
      int width_;
      int height_;
      float retina_scale_;

      glm::mat4 view_;
      glm::mat4 proj_;

      std::unique_ptr<geometry> sphere_;

      std::string log_tag_;
      std::atomic<bool> initialized_;

      glm::vec3 camera_pos_;
      glm::vec3 camera_at_;
      float pos_delta_;
    };
  }
}

#endif
