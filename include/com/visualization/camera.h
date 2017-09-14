#ifndef COM_VISUALIZATION_CAMERA_H_INCLUDED
#define COM_VISUALIZATION_CAMERA_H_INCLUDED

#include "declspec.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace com
{
  namespace visualization
  {
    class DLLSPEC_COM_VISUALIZATION camera
    {
    public:
      camera();

      const glm::mat4 &view_matrix() const;

    private:
      glm::vec3 pos_;
      glm::vec3 target_pos_;
      glm::mat4 view_matrix_;
    };
  }
}

#endif
