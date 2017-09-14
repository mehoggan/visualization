#ifndef COM_VISUALIZATION_GEOMETRY_H_INCLUDED
#define COM_VISUALIZATION_GEOMETRY_H_INCLUDED

#include "declspec.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <QOpenGLFunctions>

namespace com
{
  namespace visualization
  {
    class DLLSPEC_COM_VISUALIZATION geometry
    {
    public:
      geometry();
      virtual ~geometry();

      virtual bool initialize(QOpenGLFunctions &gl_functions) = 0;

      virtual void resize(int parent_width, int parent_height,
        float retina_scale) = 0;
      virtual void pre_draw(QOpenGLFunctions &gl_functions) = 0;
      virtual void draw(QOpenGLFunctions &gl_functions) = 0;
      virtual void post_draw(QOpenGLFunctions &gl_functions) = 0;

      virtual bool de_initialize(QOpenGLFunctions &gl_functions) = 0;

      virtual glm::mat4 compute_and_set_mvp_matrix(
        QOpenGLFunctions gl_functions,
        glm::mat4 &proj_matrix, glm::mat4 &view_matrix) = 0;

      const glm::mat4 &get_model_matrix();
      const void set_model_matrix(glm::mat4 &model_matrix);
      void update_model_matrix(glm::mat4 &model_matrix_update);

    protected:
      glm::mat4 model_;
    };
  }
}

#endif
