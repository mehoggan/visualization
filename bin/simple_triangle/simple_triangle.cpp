#include <com/visualization/application.h>
#include <com/visualization/scenes/simple_triangle.h>

#include <iostream>

int main(int argc, char *argv[])
{
  com::visualization::application bn_app(argc, argv);
  std::weak_ptr<com::visualization::main_window> main_window =
    bn_app.add_main_window();
  com::visualization::main_window &main_window_ref =
    com::visualization::main_window::from_weak_ptr(main_window);
  main_window_ref.resize(800, 600);
  main_window_ref.make_gl_widget();
  std::shared_ptr<com::visualization::scene> scene =
    std::make_shared<com::visualization::simple_triangle>();
  main_window_ref.get_gl_widget().lock()->add_scene(scene);
  main_window_ref.get_gl_widget().lock()->start_render_loop();
  scene.reset();

  return static_cast<QApplication &>(bn_app).exec();
}
