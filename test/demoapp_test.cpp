#include <gtest/gtest.h>
#include <limits>
#include <string>
#include <unordered_map>

#include "../app/demoapp.h"

using std::literals::string_literals::operator""s;
using std::string;

class DemoAppTest : public ::testing::Test {
public:
  std::unordered_map<string, string> map;
};

TEST_F(DemoAppTest, AddToMap) {
  int n = 1;
  ASSERT_EQ(n, 1);
}
