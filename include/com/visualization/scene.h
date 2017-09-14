#ifndef COM_VISUALIZATION_SCENE_H_INCLUDED
#define COM_VISUALIZATION_SCENE_H_INCLUDED

#include "declspec.h"

#include "com/visualization/enums.h"

#include <QOpenGLFunctions>

#include <cstdint>

namespace com
{
  namespace visualization
  {
    class DLLSPEC_COM_VISUALIZATION scene
    {
    public:
      scene();
      virtual ~scene();

      virtual bool initialize(QOpenGLFunctions &gl_functions) = 0;

      virtual void resize(int parent_width, int parent_height,
        float retina_scale) = 0;
      virtual void pre_draw(QOpenGLFunctions &gl_functions) = 0;
      virtual void draw(QOpenGLFunctions &gl_functions) = 0;
      virtual void post_draw(QOpenGLFunctions &gl_functions) = 0;

      virtual bool de_initialize(QOpenGLFunctions &gl_functions) = 0;

      virtual void key_press_event(int key_press_count,
        bool is_auto_repeat, std::uint32_t keyboard_modifiers,
        const char *key_sym, int key_val);
      virtual void key_release_event(int key_press_count,
        bool is_auto_repeat, std::uint32_t keyboard_modifiers,
        const char *key_sym, int key_val);
      virtual void leave_event();
      virtual void mouse_double_click_event(mouse_button button,
        std::uint32_t buttons, std::int32_t global_x, std::int32_t global_y,
        std::int32_t local_x, std::int32_t local_y, std::int32_t x,
        std::int32_t y, float screen_x, float screen_y);
      virtual void mouse_move_event(mouse_button button,
        std::uint32_t buttons, std::int32_t global_x, std::int32_t global_y,
        std::int32_t local_x, std::int32_t local_y, std::int32_t x,
        std::int32_t y, float screen_x, float screen_y);
      virtual void mouse_press_event(mouse_button button,
        std::uint32_t buttons, std::int32_t global_x, std::int32_t global_y,
        std::int32_t local_x, std::int32_t local_y, std::int32_t x,
        std::int32_t y, float screen_x, float screen_y);
      virtual void mouse_release_event(mouse_button button,
        std::uint32_t buttons, std::int32_t global_x, std::int32_t global_y,
        std::int32_t local_x, std::int32_t local_y, std::int32_t x,
        std::int32_t y, float screen_x, float screen_y);
      virtual void move_event(std::int32_t old_x, std::int32_t old_y,
        std::int32_t x, std::int32_t y);
      virtual void resize_event(std::uint32_t old_width, uint32_t old_height,
        std::uint32_t width, std::uint32_t height);
      virtual void show_event();
      virtual void wheel_event(std::int32_t x_delta, std::int32_t y_delta,
        std::uint32_t mouse_buttons, std::int32_t global_x,
        std::int32_t global_y, float global_xf, float global_yf,
        scroll_phase phase, std::int32_t pixel_delta_x,
        std::int32_t pixel_delta_y, std::int32_t x, std::int32_t y,
        float xf, float yf);
    };
  }
}

#endif
