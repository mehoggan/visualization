#ifndef COM_VISUALIZATION_LOG_HELPERS_H_INCLUDED
#define COM_VISUALIZATION_LOG_HELPERS_H_INCLUDED

#include "declspec.h"

#include <QEvent>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QMoveEvent>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QShowEvent>
#include <QWheelEvent>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <iomanip>
#include <sstream>

namespace com
{
  namespace visualization
  {
    DLLSPEC_COM_VISUALIZATION std::stringstream &operator<<(
      std::stringstream &ss, const QEvent &event);

    DLLSPEC_COM_VISUALIZATION std::stringstream &operator<<(
      std::stringstream &ss, const QKeyEvent &event);

    DLLSPEC_COM_VISUALIZATION std::stringstream &operator<<(
      std::stringstream &ss, const QMouseEvent &event);

    DLLSPEC_COM_VISUALIZATION std::stringstream &operator<<(
      std::stringstream &ss, const QMoveEvent &event);

    DLLSPEC_COM_VISUALIZATION std::stringstream &operator<<(
      std::stringstream &ss, const QPaintEvent &event);

    DLLSPEC_COM_VISUALIZATION std::stringstream &operator<<(
      std::stringstream &ss, const QResizeEvent &event);

    DLLSPEC_COM_VISUALIZATION std::stringstream &operator<<(
      std::stringstream &ss, const QShowEvent &event);

    DLLSPEC_COM_VISUALIZATION std::stringstream &operator<<(
      std::stringstream &ss, const QWheelEvent &event);

    inline std::stringstream &operator<<(std::stringstream &ss,
      const glm::mat4 &mat4)
    {
      ss << "<" << std::endl
        << "\t<"
        << std::setfill(' ') << std::setw(2) << mat4[0][0] << ", "
        << std::setfill(' ') << std::setw(2) << mat4[1][0] << ", "
        << std::setfill(' ') << std::setw(2) << mat4[2][0] << ", "
        << std::setfill(' ') << std::setw(2) << mat4[3][0] << ">\n"
        << "\t<"
        << std::setfill(' ') << std::setw(2) << mat4[0][1] << ", "
        << std::setfill(' ') << std::setw(2) << mat4[1][1] << ", "
        << std::setfill(' ') << std::setw(2) << mat4[2][1] << ", "
        << std::setfill(' ') << std::setw(2) << mat4[3][1] << ">\n"
        << "\t<"
        << std::setfill(' ') << std::setw(2) << mat4[0][2] << ", "
        << std::setfill(' ') << std::setw(2) << mat4[1][2] << ", "
        << std::setfill(' ') << std::setw(2) << mat4[2][2] << ", "
        << std::setfill(' ') << std::setw(2) << mat4[3][2] << ">\n"
        << "\t<"
        << std::setfill(' ') << std::setw(2) << mat4[0][3] << ", "
        << std::setfill(' ') << std::setw(2) << mat4[1][3] << ", "
        << std::setfill(' ') << std::setw(2) << mat4[2][3] << ", "
        << std::setfill(' ') << std::setw(2) << mat4[3][3] << ">\n"
        << ">";
      return ss;
    }

    inline std::stringstream &operator<<(std::stringstream &ss,
      const glm::vec3 &vec3)
    {
      ss << "<" << vec3[0] << ", " << vec3[1] << ", " << vec3[2] << ">";
      return ss;
    }

    template <typename T>
    inline std::stringstream &operator<<(std::stringstream &ss,
      const std::vector<T> &vec)
    {
      for (const T &i : vec) {
        ss << i << " ";
      }

      return ss;
    }
  }
}

#endif
