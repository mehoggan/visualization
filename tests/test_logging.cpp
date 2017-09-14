#include <gtest/gtest.h>

#include <com/visualization/logging.h>

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <streambuf>


namespace com
{
  namespace visualization
  {
    class TestLogging : public ::testing::Test
    {
    protected:
      virtual void SetUp()
      {
        logging::init();
      }

      virtual void TearDown()
      {}
    };

    TEST_F(TestLogging, does_tag_sink_filtering_work)
    {
      logging::add_std_log_logger("TAGA", INFO);
      logging::debug("TAGA", "Hello World");
      logging::add_std_cerr_logger("TAGB");
      logging::error("TAGB", "Goodbye World!");
      logging::add_std_cerr_logger("TAGC");
      logging::error("TAGC", "Goodbye World!!");
      logging::add_std_cerr_logger("TAGD");
      logging::error("TAGD", "Goodbye World!!!");
    }

    TEST_F(TestLogging, mktmpdir_makes_tmp_dir_and_correct_logs_written)
    {
      const char *tag = "mktmpdir_makes_tmp_dir";
      logging::add_std_log_logger(tag, DEBUG);
      boost::filesystem::path tmpdir = logging::mktmpdir();
      boost::filesystem::path log_path = tmpdir / "logs.lg";
      logging::add_file_logger("FILE_LOGGER", log_path, INFO);
      for (std::size_t i = 0; i < 20; ++i) {
        logging::info("FILE_LOGGER", "Hello World", i);
      }

      EXPECT_TRUE(boost::filesystem::exists(tmpdir));
      EXPECT_TRUE(boost::filesystem::is_directory(tmpdir));
      EXPECT_TRUE(boost::filesystem::exists(log_path));

      sleep(1);

      std::ifstream ifs(log_path.string());
      std::string line;
      std::size_t i = 0;
      while(std::getline(ifs, line)) {
        std::stringstream ss;
        ss << "Hello World " << i;
        EXPECT_TRUE(line.find(ss.str(), 0) != std::string::npos) <<
          ss.str() << " not in " << line;
        ++i;
      }


      boost::filesystem::remove_all(tmpdir);
    }
  }
}
