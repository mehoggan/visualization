#include "com/visualization/camera.h"

namespace com
{
  namespace visualization
  {
    camera::camera() :
      pos_(0.0f, 0.0f, 1.0f),
      target_pos_(0.0f, 0.0f, 0.0f),
      view_matrix_(glm::lookAt(
        pos_,
        target_pos_,
        glm::vec3(0.0f, 1.0f, 0.0f)))
    {}

    const glm::mat4 &camera::view_matrix() const
    {
      return view_matrix_;
    }
  }
}
