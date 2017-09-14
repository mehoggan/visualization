#include "com/visualization/main_window.h"

#include "com/visualization/logging.h"

#include <QPalette>

namespace com
{
  namespace visualization
  {
    main_window::main_window(QWidget *parent) :
      QMainWindow(parent),
      log_tag_(logging::log_tag_for_this(*this))
    {
      logging::add_std_log_logger(log_tag_, DEBUG);
    }

    main_window::~main_window()
    {}

    void main_window::make_gl_widget()
    {
      gl_widget_.reset(new gl_widget(this));
      gl_widget_.get()->setSizePolicy(QSizePolicy::Expanding,
        QSizePolicy::Expanding);

      QWidget *central_widget = new QWidget(this);
      central_widget->setSizePolicy(QSizePolicy::Expanding,
        QSizePolicy::Expanding);
      main_layout_.reset(new QHBoxLayout(this));
      central_widget->setLayout(main_layout_.get());
      main_layout_.get()->addWidget(gl_widget_.get());
      main_layout_.get()->setContentsMargins(0, 0, 0, 0);

      QPalette pal = palette();
      pal.setColor(QPalette::Background, Qt::red);
      central_widget->setAutoFillBackground(true);
      central_widget->setPalette(pal);
      central_widget->show();

      QMainWindow::setCentralWidget(central_widget);
    }

    std::weak_ptr<gl_widget> main_window::get_gl_widget()
    {
      return std::weak_ptr<gl_widget>(gl_widget_);
    }

    main_window &main_window::from_weak_ptr(std::weak_ptr<main_window> mw)
    {
      return *(mw.lock().get());
    }

    void main_window::keyPressEvent(QKeyEvent *event)
    {
      QMainWindow::keyPressEvent(event);
      if (gl_widget_) {
        gl_widget_->key_press_event(event);
      }
    }

    void main_window::keyReleaseEvent(QKeyEvent *event)
    {
      QMainWindow::keyReleaseEvent(event);
      if (gl_widget_) {
        gl_widget_->key_release_event(event);
      }
    }

    void main_window::leaveEvent(QEvent *event)
    {
      QMainWindow::leaveEvent(event);
      if (gl_widget_) {
        gl_widget_->leave_event(event);
      }
    }

    void main_window::mouseDoubleClickEvent(QMouseEvent *event)
    {
      QMainWindow::mouseDoubleClickEvent(event);
      if (gl_widget_) {
        gl_widget_->mouse_double_click_event(event);
      }
    }

    void main_window::mouseMoveEvent(QMouseEvent *event)
    {
      QMainWindow::mouseMoveEvent(event);
      if (gl_widget_) {
        gl_widget_->mouse_move_event(event);
      }
    }

    void main_window::mousePressEvent(QMouseEvent *event)
    {
      QMainWindow::mousePressEvent(event);
      if (gl_widget_) {
        gl_widget_->mouse_press_event(event);
      }
    }

    void main_window::mouseReleaseEvent(QMouseEvent *event)
    {
      QMainWindow::mouseReleaseEvent(event);
      if (gl_widget_) {
        gl_widget_->mouse_release_event(event);
      }
    }

    void main_window::moveEvent(QMoveEvent *event)
    {
      QMainWindow::moveEvent(event);
      if (gl_widget_) {
        gl_widget_->move_event(event);
      }
    }

    void main_window::resizeEvent(QResizeEvent *event)
    {
      QMainWindow::resizeEvent(event);
      if (gl_widget_) {
        gl_widget_->resize_event(event);
      }
    }

    void main_window::showEvent(QShowEvent *event)
    {
      QMainWindow::showEvent(event);
      if (gl_widget_) {
        gl_widget_->show_event(event);
      }
    }

    void main_window::wheelEvent(QWheelEvent *event)
    {
      QMainWindow::wheelEvent(event);
      if (gl_widget_) {
        gl_widget_->wheel_event(event);
      }
    }
  }
}
