#include "com/visualization/gl_widget.h"

#include "com/visualization/gl_helpers.h"
#include "com/visualization/logging.h"

namespace com
{
  namespace visualization
  {
    gl_widget::gl_widget(QWidget *parent) :
      QGLWidget(parent),
      render_timer_(new QTimer(this)),
      initialized_(false),
      shown_(false),
      log_tag_(logging::log_tag_for_this(*this))
    {
      connect(render_timer_.get(), &QTimer::timeout, this, &gl_widget::draw);
      logging::add_std_log_logger(log_tag_, INFO);
    }

    gl_widget::~gl_widget()
    {
      stop_render_loop();
      render_timer_.reset();

      makeCurrent();

      // Release all resources.
      if (cleanup_callback_) {
        cleanup_callback_(this);
      }

      {
        std::lock_guard<std::mutex> lock{scene_lock_};
        for (std::shared_ptr<scene> s : scenes_) {
          s->de_initialize(dynamic_cast<QOpenGLFunctions &>(*this));
        }
        scenes_to_init_.clear();
      }

      doneCurrent();
    }

    void gl_widget::start_render_loop(int msec)
    {
      stop_render_loop();
      render_timer_->start(msec);
    }

    void gl_widget::stop_render_loop()
    {
      render_timer_->stop();
    }

    void gl_widget::set_bottom_level_draw_callback(
      std::function<void (QOpenGLFunctions *)> &cb)
    {
      bottom_level_draw_callback_ = cb;
    }

    void gl_widget::set_top_level_draw_callback(
      std::function<void (QOpenGLFunctions *)> &cb)
    {
      top_level_draw_callback_ = cb;
    }

    void gl_widget::set_cleanup_callback(
      std::function<void (QOpenGLFunctions *)> &cb)
    {
      cleanup_callback_ = cb;
    }

    void gl_widget::set_init_callback(
      std::function<void (QOpenGLFunctions *)> &cb)
    {
      init_callback_ = cb;
    }

    void gl_widget::hideEvent(QHideEvent *event)
    {
      QWidget::hideEvent(event);
      shown_.store(false);
    }

    void gl_widget::showEvent(QShowEvent *event) {
      QWidget::showEvent(event);
      shown_.store(true);
    }

    void gl_widget::add_scene(std::shared_ptr<scene> &s)
    {
      {
        std::lock_guard<std::mutex> lock{scene_lock_};
        scenes_to_init_.push_back(s);
        scenes_.push_back(s);
      }
    }

    void gl_widget::key_press_event(QKeyEvent *event)
    {
      static_assert(sizeof(keyboard_modifiers::no_modifier) ==
        sizeof(std::uint32_t), "com::visualization::keyboard_modifier"
        " is not 32 bit.");
      static_assert(sizeof(Qt::KeyboardModifier) ==
        sizeof(std::uint32_t), "Qt::KeyboardModifier is not 32 bit.");

      logging::debug(log_tag_, (*event));
      if (event) {
        std::lock_guard<std::mutex> lock{scene_lock_};
        for (std::shared_ptr<scene> s : scenes_) {
          s->key_press_event(event->count(), event->isAutoRepeat(),
            static_cast<std::uint32_t>(event->modifiers()),
            event->text().toStdString().c_str(), event->key());
        }
      }
    }

    void gl_widget::key_release_event(QKeyEvent *event)
    {
      static_assert(sizeof(keyboard_modifiers::no_modifier) ==
        sizeof(std::uint32_t), "com::visualization::keyboard_modifier"
        " is not 32 bit.");
      static_assert(sizeof(Qt::KeyboardModifier) ==
        sizeof(std::uint32_t), "Qt::KeyboardModifier is not 32 bit.");

      logging::debug(log_tag_, (*event));
      if (event) {
        std::lock_guard<std::mutex> lock{scene_lock_};
        for (std::shared_ptr<scene> s : scenes_) {
          s->key_release_event(event->count(), event->isAutoRepeat(),
            static_cast<std::uint32_t>(event->modifiers()),
            event->text().toStdString().c_str(), event->key());
        }
      }
    }

    void gl_widget::leave_event(QEvent *event)
    {
      logging::debug(log_tag_, (*event));
      {
        std::lock_guard<std::mutex> lock{scene_lock_};
        for (std::shared_ptr<scene> s : scenes_) {
          s->leave_event();
        }
      }
    }

    void gl_widget::mouse_double_click_event(QMouseEvent *event)
    {
      static_assert(sizeof(mouse_button::no_button) ==
        sizeof(std::uint32_t), "com::visualization::mouse_button"
        " is not 32 bit.");
      static_assert(sizeof(Qt::MouseButton) ==
        sizeof(std::uint32_t), "Qt::MouseButton is not 32 bit.");

      logging::debug(log_tag_, (*event));
      if (event) {
        std::lock_guard<std::mutex> lock{scene_lock_};
        for (std::shared_ptr<scene> s : scenes_) {
          s->mouse_double_click_event(
            static_cast<mouse_button>(event->button()),
            static_cast<std::uint32_t>(event->buttons()),
            event->globalPos().x(), event->globalPos().y(),
            event->localPos().x(), event->localPos().y(),
            event->pos().x(), event->pos().y(),
            event->screenPos().x(), event->screenPos().y());
        }
      }
    }

    void gl_widget::mouse_move_event(QMouseEvent *event)
    {
      static_assert(sizeof(mouse_button::no_button) ==
        sizeof(std::uint32_t), "com::visualization::mouse_button"
        " is not 32 bit.");
      static_assert(sizeof(Qt::MouseButton) ==
        sizeof(std::uint32_t), "Qt::MouseButton is not 32 bit.");

      logging::debug(log_tag_, (*event));
      if (event) {
        std::lock_guard<std::mutex> lock{scene_lock_};
        for (std::shared_ptr<scene> s : scenes_) {
          s->mouse_move_event(
            static_cast<mouse_button>(event->button()),
            static_cast<std::uint32_t>(event->buttons()),
            event->globalPos().x(), event->globalPos().y(),
            event->localPos().x(), event->localPos().y(),
            event->pos().x(), event->pos().y(),
            event->screenPos().x(), event->screenPos().y());
        }
      }
    }

    void gl_widget::mouse_press_event(QMouseEvent *event)
    {
      static_assert(sizeof(mouse_button::no_button) ==
        sizeof(std::uint32_t), "com::visualization::mouse_button"
        " is not 32 bit.");
      static_assert(sizeof(Qt::MouseButton) ==
        sizeof(std::uint32_t), "Qt::MouseButton is not 32 bit.");

      logging::debug(log_tag_, (*event));
      if (event) {
        std::lock_guard<std::mutex> lock{scene_lock_};
        for (std::shared_ptr<scene> s : scenes_) {
          s->mouse_press_event(
            static_cast<mouse_button>(event->button()),
            static_cast<std::uint32_t>(event->buttons()),
            event->globalPos().x(), event->globalPos().y(),
            event->localPos().x(), event->localPos().y(),
            event->pos().x(), event->pos().y(),
            event->screenPos().x(), event->screenPos().y());
        }
      }
    }

    void gl_widget::mouse_release_event(QMouseEvent *event)
    {
      static_assert(sizeof(mouse_button::no_button) ==
        sizeof(std::uint32_t), "com::visualization::mouse_button"
        " is not 32 bit.");
      static_assert(sizeof(Qt::MouseButton) ==
        sizeof(std::uint32_t), "Qt::MouseButton is not 32 bit.");

      logging::debug(log_tag_, (*event));
      if (event) {
        std::lock_guard<std::mutex> lock{scene_lock_};
        for (std::shared_ptr<scene> s : scenes_) {
          s->mouse_release_event(
            static_cast<mouse_button>(event->button()),
            static_cast<std::uint32_t>(event->buttons()),
            event->globalPos().x(), event->globalPos().y(),
            event->localPos().x(), event->localPos().y(),
            event->pos().x(), event->pos().y(),
            event->screenPos().x(), event->screenPos().y());
        }
      }
    }

    void gl_widget::move_event(QMoveEvent *event)
    {
      logging::debug(log_tag_, (*event));
      if (event) {
        std::lock_guard<std::mutex> lock{scene_lock_};
        for (std::shared_ptr<scene> s : scenes_) {
          s->move_event(event->oldPos().x(), event->oldPos().y(),
            event->pos().x(), event->pos().y());
        }
      }
    }

    void gl_widget::resize_event(QResizeEvent *event)
    {
      logging::debug(log_tag_, (*event));
      if (event) {
        std::lock_guard<std::mutex> lock{scene_lock_};
        for (std::shared_ptr<scene> s : scenes_) {
          s->resize_event(event->oldSize().width(),
            event->oldSize().height(), event->size().width(),
            event->size().height());
        }
      }
    }

    void gl_widget::show_event(QShowEvent *event)
    {
      logging::debug(log_tag_, (*event));
      {
        std::lock_guard<std::mutex> lock{scene_lock_};
        for (std::shared_ptr<scene> s : scenes_) {
          s->show_event();
        }
      }
    }

    void gl_widget::wheel_event(QWheelEvent *event)
    {
      static_assert(sizeof(scroll_phase::no_scroll_phase) ==
        sizeof(std::uint32_t), "com::visualization::scroll_phase"
        " is not 32 bit.");
      static_assert(sizeof(Qt::ScrollPhase) ==
        sizeof(std::uint32_t), "Qt::ScrollPhase is not 32 bit.");

      logging::debug(log_tag_, (*event));
      if (event) {
        std::lock_guard<std::mutex> lock{scene_lock_};
        for (std::shared_ptr<scene> s : scenes_) {
          s->wheel_event(event->angleDelta().x(), event->angleDelta().y(),
            static_cast<std::uint32_t>(event->buttons()),
            event->globalPos().x(), event->globalPos().y(),
            event->globalPosF().x(), event->globalPos().y(),
            static_cast<scroll_phase>(event->phase()),
            event->pixelDelta().x(), event->pixelDelta().y(),
            event->pos().x(), event->pos().y(),
            event->posF().x(), event->posF().y());
        }
      }
    }

    void gl_widget::draw()
    {
      paintGL();
    }

    void gl_widget::initializeGL()
    {
      makeCurrent();
      QOpenGLFunctions::initializeOpenGLFunctions();

      if (init_callback_) {
        init_callback_(this);
      }

      if (!initialized_.load()) {
        initialized_.store(true);
      }

      doneCurrent();
    }

    void gl_widget::paintGL()
    {
      if (!shown_.load()) {
        return;
      }

      makeCurrent();

      {
        std::lock_guard<std::mutex> lock{scene_lock_};
        for (std::shared_ptr<scene> s : scenes_to_init_) {
          s->initialize(dynamic_cast<QOpenGLFunctions &>(*this));
        }
        scenes_to_init_.clear();
      }

      std::string log_tag = logging::log_tag_for_this(*this);

      const float retina_scale = devicePixelRatio();

      glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
      GL_CALL_BASE("glClearColor", log_tag)
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      GL_CALL_BASE("glClear", log_tag)
      glViewport(0, 0, width() * retina_scale, height() * retina_scale);
      GL_CALL_BASE("glViewport", log_tag)

      if (top_level_draw_callback_) {
        top_level_draw_callback_(this);
      }

      {
        std::lock_guard<std::mutex> lock{scene_lock_};
        for (std::shared_ptr<scene> s : scenes_) {
          if (s) {
            s->pre_draw(dynamic_cast<QOpenGLFunctions &>(*this));
            s->draw(dynamic_cast<QOpenGLFunctions &>(*this));
            s->post_draw(dynamic_cast<QOpenGLFunctions &>(*this));
          }
        }
      }

      if (bottom_level_draw_callback_) {
        bottom_level_draw_callback_(this);
      }

      QGLWidget::swapBuffers();
      doneCurrent();
    }

    void gl_widget::resizeGL(int width, int height)
    {
      std::string log_tag = logging::log_tag_for_this(*this);

      const float retina_scale = devicePixelRatio();

      makeCurrent();
      glViewport(0, 0, width, height);
      GL_CALL_BASE("glViewport", log_tag)
      {
        std::lock_guard<std::mutex> lock{scene_lock_};
        for (std::shared_ptr<scene> &s : scenes_) {
          if (s) {
            s->resize(width, height, retina_scale);
          }
        }
      }
      doneCurrent();
    }
  }
}
