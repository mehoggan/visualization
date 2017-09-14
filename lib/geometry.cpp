#include "com/visualization/geometry.h"

namespace com
{
  namespace visualization
  {
    geometry::geometry() :
      model_(1.0f)
    {}

    geometry::~geometry()
    {}

    const glm::mat4 &geometry::get_model_matrix()
    {
      return model_;
    }

    const void geometry::set_model_matrix(glm::mat4 &model_matrix)
    {
      model_ = model_matrix;
    }

    void geometry::update_model_matrix(glm::mat4 &model_matrix_update)
    {
      model_ *= model_matrix_update;
    }
  }
}
