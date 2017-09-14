#include "com/visualization/scene.h"

namespace com
{
  namespace visualization
  {
    scene::scene()
    {}

    scene::~scene()
    {}

    void scene::key_press_event(int key_press_count, bool is_auto_repeat,
      std::uint32_t keyboard_modifiers, const char *key_sym, int key_val)
    {
      (void)key_press_count;
      (void)is_auto_repeat;
      (void)keyboard_modifiers;
      (void)key_sym;
      (void)key_val;
    }

    void scene::key_release_event(int key_press_count,
        bool is_auto_repeat, std::uint32_t keyboard_modifiers,
        const char *key_sym, int key_val)
    {
      (void)key_press_count;
      (void)is_auto_repeat;
      (void)keyboard_modifiers;
      (void)key_sym;
      (void)key_val;
    }

    void scene::leave_event()
    {}

    void scene::mouse_double_click_event(mouse_button button,
      std::uint32_t buttons, std::int32_t global_x, std::int32_t global_y,
      std::int32_t local_x, std::int32_t local_y, std::int32_t x,
      std::int32_t y, float screen_x, float screen_y)
    {
      (void)buttons;
      (void)global_x;
      (void)global_y;
      (void)local_x;
      (void)local_y;
      (void)x;
      (void)y;
      (void)screen_x;
      (void)screen_y;
    }

    void scene::mouse_move_event(mouse_button button,
      std::uint32_t buttons, std::int32_t global_x, std::int32_t global_y,
      std::int32_t local_x, std::int32_t local_y, std::int32_t x,
      std::int32_t y, float screen_x, float screen_y)
    {
      (void)buttons;
      (void)global_x;
      (void)global_y;
      (void)local_x;
      (void)local_y;
      (void)x;
      (void)y;
      (void)screen_x;
      (void)screen_y;
    }

    void scene::mouse_press_event(mouse_button button,
      std::uint32_t buttons, std::int32_t global_x, std::int32_t global_y,
      std::int32_t local_x, std::int32_t local_y, std::int32_t x,
      std::int32_t y, float screen_x, float screen_y)
    {
      (void)buttons;
      (void)global_x;
      (void)global_y;
      (void)local_x;
      (void)local_y;
      (void)x;
      (void)y;
      (void)screen_x;
      (void)screen_y;
    }

    void scene::mouse_release_event(mouse_button button,
      std::uint32_t buttons, std::int32_t global_x, std::int32_t global_y,
      std::int32_t local_x, std::int32_t local_y, std::int32_t x,
      std::int32_t y, float screen_x, float screen_y)
    {
      (void)buttons;
      (void)global_x;
      (void)global_y;
      (void)local_x;
      (void)local_y;
      (void)x;
      (void)y;
      (void)screen_x;
      (void)screen_y;
    }

    void scene::move_event(std::int32_t old_x, std::int32_t old_y,
      std::int32_t x, std::int32_t y)
    {
      (void)old_x;
      (void)old_y;
      (void)x;
      (void)y;
    }

    void scene::resize_event(std::uint32_t old_width, uint32_t old_height,
      std::uint32_t width, std::uint32_t height)
    {
      (void)old_width;
      (void)old_height;
      (void)width;
      (void)height;
    }

    void scene::show_event()
    {}

    void scene::wheel_event(std::int32_t x_delta, std::int32_t y_delta,
        std::uint32_t mouse_buttons, std::int32_t global_x,
        std::int32_t global_y, float global_xf, float global_yf,
        scroll_phase phase, std::int32_t pixel_delta_x,
        std::int32_t pixel_delta_y, std::int32_t x, std::int32_t y,
        float xf, float yf)
    {
      (void)x_delta;
      (void)y_delta;
      (void)mouse_buttons;
      (void)global_x;
      (void)global_y;
      (void)global_xf;
      (void)global_yf;
      (void)phase;
      (void)pixel_delta_x;
      (void)pixel_delta_y;
      (void)x;
      (void)y;
      (void)xf;
      (void)yf;
    }
  }
}
