#include <gtest/gtest.h>

#include <com/visualization/camera.h>
#include <com/visualization/logging.h>

#include <string>

namespace com
{
  namespace visualization
  {
    class TestCamera : public ::testing::Test
    {
    protected:
      virtual void SetUp()
      {
        log_tag_ = logging::log_tag_for_this(*this);
        logging::add_std_cout_logger(log_tag_, DEBUG);
      }

      virtual void TearDown()
      {}

      const std::string &log_tag() { return log_tag_; }

      std::string log_tag_;
    };

    TEST_F(TestCamera, ctor)
    {
      camera c;
      logging::debug(log_tag(), "view_matrix =\n", c.view_matrix());
    }
  }
}
