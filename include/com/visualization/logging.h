#ifndef COM_VISUALIZATION_LOGGING_H_INCLUDED
#define COM_VISUALIZATION_LOGGING_H_INCLUDED

#define BOOST_LOG_DYN_LINK 1

#include "declspec.h"

#include "com/visualization/log_helpers.h"

#include <boost/log/trivial.hpp>
#include <boost/filesystem/path.hpp>

#include <atomic>
#include <sstream>
#include <string>
#include <unordered_map>

#define TRACE boost::log::trivial::severity_level::trace
#define DEBUG boost::log::trivial::severity_level::debug
#define INFO boost::log::trivial::severity_level::info
#define WARN boost::log::trivial::severity_level::warning
#define ERROR boost::log::trivial::severity_level::error
#define FATAL boost::log::trivial::severity_level::fatal

namespace com
{
  namespace visualization
  {
    class DLLSPEC_COM_VISUALIZATION logging
    {
    public:
      static void add_std_cout_logger(const std::string &tag,
        boost::log::trivial::severity_level level = INFO);
      static void add_std_cerr_logger(const std::string &tag,
        boost::log::trivial::severity_level level = ERROR);
      static void add_std_log_logger(const std::string &tag,
        boost::log::trivial::severity_level level = TRACE);
      static void add_file_logger(const std::string &tag,
        const boost::filesystem::path &log_path,
        boost::log::trivial::severity_level level = INFO);

      template<typename T>
      static std::string log_tag_for_this(T &instance)
      {
        std::stringstream ss;
        ss << typeid(T).name() << "_" << (&(instance));
        return ss.str();
      }

    public:
      static bool init();

      static boost::filesystem::path mktmpdir(
        const boost::filesystem::path &model = "%%%%-%%%%-%%%%-%%%%");

      template<typename ...Ts>
      static void trace(const std::string &tag, Ts&&... args)
      {
        std::stringstream ss;
        log_string_builder(ss, args...);
        write_severity_log(tag, TRACE, ss.str());
      }

      template<typename ...Ts>
      static void debug(const std::string &tag, Ts&&... args)
      {
        std::stringstream ss;
        log_string_builder(ss, args...);
        write_severity_log(tag, DEBUG, ss.str());
      }

      template<typename ...Ts>
      static void info(const std::string &tag, Ts&&... args)
      {
        std::stringstream ss;
        log_string_builder(ss, args...);
        write_severity_log(tag, INFO, ss.str());
      }

      template<typename ...Ts>
      static void warn(const std::string &tag, Ts&&... args)
      {
        std::stringstream ss;
        log_string_builder(ss, args...);
        write_severity_log(tag, WARN, ss.str());
      }

      template<typename ...Ts>
      static void error(const std::string &tag, Ts&&... args)
      {
        std::stringstream ss;
        log_string_builder(ss, args...);
        write_severity_log(tag, ERROR, ss.str());
      }

      template<typename ...Ts>
      static void fatal(const std::string &tag, Ts&&... args)
      {
        std::stringstream ss;
        log_string_builder(ss, args...);
        write_severity_log(tag, FATAL, ss.str());
      }

    private:
      template<typename T>
      static void log_string_builder(std::stringstream &ss, T &&arg)
      {
        ss << std::forward<T>(arg);
      }

      template<typename T, typename... Ts>
      static void log_string_builder(std::stringstream &ss, T &&arg,
        Ts&&... args)
      {
        ss << std::forward<T>(arg) << " ";
        log_string_builder(ss, args...);
      }

      static void write_severity_log(
        const std::string &tag,
        boost::log::trivial::severity_level level,
        const std::string &message);

    private:
      std::string tag_;

    private:
      static std::atomic<bool> init_;
      static std::unordered_map<std::size_t, logging> loggers_;
      friend class std::unordered_map<std::size_t, logging>;
    };
  }
}
#endif
