#ifndef COM_VISUALIZATION_MAIN_WINDOW_H_INCLUDED
#define COM_VISUALIZATION_MAIN_WINDOW_H_INCLUDED

#include "declspec.h"

#include "com/visualization/gl_widget.h"

#include <QEvent>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QMainWindow>
#include <QMouseEvent>
#include <QMoveEvent>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QShowEvent>
#include <QWheelEvent>

#include <memory>

namespace com
{
  namespace visualization
  {
    class DLLSPEC_COM_VISUALIZATION main_window : public QMainWindow
    {
      Q_OBJECT

    public:
      explicit main_window(QWidget *parent = nullptr);
      virtual ~main_window();

      void make_gl_widget();
      std::weak_ptr<gl_widget> get_gl_widget();

      static main_window &from_weak_ptr(std::weak_ptr<main_window> mw);

    public:
      virtual void keyPressEvent(QKeyEvent *event) override;
      virtual void keyReleaseEvent(QKeyEvent *event) override;
      virtual void leaveEvent(QEvent *event) override;
      virtual void mouseDoubleClickEvent(QMouseEvent *event) override;
      virtual void mouseMoveEvent(QMouseEvent *event) override;
      virtual void mousePressEvent(QMouseEvent *event) override;
      virtual void mouseReleaseEvent(QMouseEvent *event) override;
      virtual void moveEvent(QMoveEvent *event) override;
      virtual void resizeEvent(QResizeEvent *event) override;
      virtual void showEvent(QShowEvent *event) override;
      virtual void wheelEvent(QWheelEvent *event) override;

    private:
      std::shared_ptr<gl_widget> gl_widget_;
      std::unique_ptr<QHBoxLayout> main_layout_;
      std::string log_tag_;
    };
  }
}

#endif
