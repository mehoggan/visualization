#include "com/visualization/scenes/indexed_rainbow_sphere.h"

#include "com/visualization/geometries/sphere.h"
#include "com/visualization/gl_helpers.h"

#include "opengl_graphics/mesh_types/datums/interleaved_datum_2d.h"

namespace com
{
  namespace visualization
  {
    // Shader sources
    indexed_rainbow_sphere::indexed_rainbow_sphere() :
      width_(0),
      height_(0),
      retina_scale_(1.0),
      view_(1.0f),
      proj_(1.0f),
      sphere_(new sphere),
      log_tag_(logging::log_tag_for_this(*this)),
      initialized_(false),
      camera_pos_(0.0f, 0.0f, 10.0f),
      camera_at_(0.0f, 0.0f, 0.0f),
      pos_delta_(0.1f)
    {
      logging::add_std_log_logger(log_tag_, INFO);
    }

    indexed_rainbow_sphere::~indexed_rainbow_sphere()
    {}

    bool indexed_rainbow_sphere::initialize(
      QOpenGLFunctions &gl_functions)
    {
      if (!initialized_.load()) {
        bool sphere_init = sphere_->initialize(gl_functions);
        if (sphere_init) {
          initialized_.store(true);
        }
      }

      return initialized_.load();
    }

    void indexed_rainbow_sphere::resize(int parent_width,
      int parent_height, float retina_scale)
    {
      sphere_->resize(parent_width, parent_height, retina_scale);

      width_ = static_cast<int>(1.0 * parent_width);
      height_ = static_cast<int>(1.0 * parent_height);
      retina_scale_ = retina_scale;
    }

    void indexed_rainbow_sphere::pre_draw(QOpenGLFunctions &gl_functions)
    {
      sphere_->pre_draw(gl_functions);

      view_ = glm::lookAt(
        camera_pos_,
        camera_at_,
        glm::vec3(+0.0f, +1.0f, +0.0f));

      proj_ = glm::perspective(glm::radians(45.0f),
        width_ / height_ * retina_scale_, 0.2f, 1000000.0f);

      sphere_->compute_and_set_mvp_matrix(gl_functions, proj_, view_);
    }

    void indexed_rainbow_sphere::draw(QOpenGLFunctions &gl_functions)
    {
      sphere_->draw(gl_functions);
    }

    void indexed_rainbow_sphere::post_draw(QOpenGLFunctions &gl_functions)
    {
      sphere_->post_draw(gl_functions);
    }

    bool indexed_rainbow_sphere::de_initialize(
      QOpenGLFunctions &gl_functions)
    {
      return sphere_->de_initialize(gl_functions);
    }

    void indexed_rainbow_sphere::wheel_event(
      std::int32_t x_delta, std::int32_t y_delta,
      std::uint32_t mouse_buttons, std::int32_t global_x,
      std::int32_t global_y, float global_xf, float global_yf,
      scroll_phase phase, std::int32_t pixel_delta_x,
      std::int32_t pixel_delta_y, std::int32_t x, std::int32_t y,
      float xf, float yf)
    {
      scene::wheel_event(x_delta, y_delta, mouse_buttons, global_x,
        global_y, global_xf, global_yf, phase, pixel_delta_x,
        pixel_delta_y, x, y, xf, yf);

      if (y_delta < 0) {
        camera_pos_[2] -= pos_delta_;
      } else if (y_delta > 0) {
        camera_pos_[2] += pos_delta_;
      }
    }

    void indexed_rainbow_sphere::key_press_event(int key_press_count,
      bool is_auto_repeat, std::uint32_t keyboard_modifiers,
      const char *key_sym, int key_val)
    {
      scene::key_press_event(key_press_count, is_auto_repeat,
        keyboard_modifiers, key_sym, key_val);

      switch (key_val) {
      case 16777234: { // Left arrow
        camera_pos_[0] -= pos_delta_;
      }
        break;
      case 16777235: { // Up arrow
        camera_pos_[1] += pos_delta_;
      }
        break;
      case 16777236: {
        camera_pos_[0] += pos_delta_;
      }
        break;
      case 16777237: { // Down arrow
        camera_pos_[1] -= pos_delta_;
      }
        break;
      default : {
      }
        break;
      }
    }
  }
}
