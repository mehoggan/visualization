#ifndef COM_VISUALIZATION_APPLICATION_H_INCLUDED
#define COM_VISUALIZATION_APPLICATION_H_INCLUDED

#include "declspec.h"

#include "com/visualization/main_window.h"

#include "boost/filesystem/path.hpp"

#include <QApplication>

#include <memory>
#include <vector>

namespace com
{
  namespace visualization
  {
    class DLLSPEC_COM_VISUALIZATION application : public QApplication
    {
      Q_OBJECT

    public:
      application(int &argc, char **argv);
      virtual ~application();

      virtual bool notify(QObject *receiver, QEvent *e);
      virtual bool event(QEvent *e);

      std::weak_ptr<main_window> add_main_window(bool show = true);

      main_window &from_weak_ptr(std::weak_ptr<main_window> mw);

      static const boost::filesystem::path &exe_path();
      static const boost::filesystem::path &exe_dir();

    private:
      std::vector<std::shared_ptr<main_window>> main_windows_;

    private:
      static boost::filesystem::path exe_path_;
      static boost::filesystem::path exe_dir_;
    };
  }
}

#endif
