#include "com/visualization/application.h"

#include <QtWidgets>

#include <iostream>

namespace com
{
  namespace visualization
  {

    boost::filesystem::path application::exe_path_ = "";
    boost::filesystem::path application::exe_dir_ = "";

    application::application(int &argc, char **argv) :
      QApplication(argc, argv)
    {
      application::exe_path_ = argv[0];
      application::exe_dir_ = exe_path_.parent_path();
    }

    application::~application()
    {}

    bool application::notify(QObject *receiver, QEvent *e)
    {
      return QApplication::notify(receiver, e);
    }

    bool application::event(QEvent *e)
    {
      return QApplication::event(e);
    }

    std::weak_ptr<main_window> application::add_main_window(bool show)
    {
      std::shared_ptr<main_window> window(new main_window());

      main_windows_.push_back(window);

      if (show) {
        main_windows_.back()->show();
      }

      return std::weak_ptr<main_window>(main_windows_.back());
    }

    const boost::filesystem::path &application::exe_path()
    {
      return exe_path_;
    }

    const boost::filesystem::path &application::exe_dir()
    {
      return exe_dir_;
    }
  }
}
