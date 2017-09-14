#ifndef COM_VISUALIZATION_GL_WIDGET_H_INCLUDED
#define COM_VISUALIZATION_GL_WIDGET_H_INCLUDED

#include "declspec.h"

#include "com/visualization/scene.h"

#include <QtOpenGL/QGLWidget>
#include <QHideEvent>
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
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QShowEvent>
#include <QTimer>

#include <atomic>
#include <functional>
#include <memory>
#include <mutex>
#include <vector>

namespace com
{
  namespace visualization
  {
    class DLLSPEC_COM_VISUALIZATION gl_widget :
      public QGLWidget, protected QOpenGLFunctions
    {
      Q_OBJECT

    public:
      explicit gl_widget(QWidget *parent = nullptr);
      virtual ~gl_widget();

      void start_render_loop(int msec = 16);
      void stop_render_loop();

      void set_top_level_draw_callback(
        std::function<void (QOpenGLFunctions *)> &cb);
      void set_bottom_level_draw_callback(
        std::function<void (QOpenGLFunctions *)> &cb);
      void set_cleanup_callback(
        std::function<void (QOpenGLFunctions *)> &cb);
      void set_init_callback(
        std::function<void (QOpenGLFunctions *)> &cb);

      void add_scene(std::shared_ptr<scene> &s);

      void key_press_event(QKeyEvent *event);
      void key_release_event(QKeyEvent *event);
      void leave_event(QEvent *event);
      void mouse_double_click_event(QMouseEvent *event);
      void mouse_move_event(QMouseEvent *event);
      void mouse_press_event(QMouseEvent *event);
      void mouse_release_event(QMouseEvent *event);
      void move_event(QMoveEvent *event);
      void resize_event(QResizeEvent *event);
      void show_event(QShowEvent *event);
      void wheel_event(QWheelEvent *event);

    public:
      void hideEvent(QHideEvent *event) override;
      void showEvent(QShowEvent *event) override;

    protected slots:
      void draw();

    protected:
      void initializeGL() override;
      void paintGL() override;
      void resizeGL(int width, int height) override;

    private:
      std::function<void (QOpenGLFunctions *)> bottom_level_draw_callback_;
      std::function<void (QOpenGLFunctions *)> top_level_draw_callback_;
      std::function<void (QOpenGLFunctions *)> cleanup_callback_;
      std::function<void (QOpenGLFunctions *)> init_callback_;
      std::unique_ptr<QTimer> render_timer_;
      std::atomic<bool> initialized_;
      std::atomic<bool> shown_;

      std::mutex scene_lock_;
      std::vector<std::shared_ptr<scene>> scenes_;
      std::vector<std::shared_ptr<scene>> scenes_to_init_;
      std::string log_tag_;
    };
  }
}

#endif
