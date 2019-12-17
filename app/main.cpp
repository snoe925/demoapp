#include <array>
#include <atomic>
#include <deque>
#include <iostream>
#include <mutex>
#include <signal.h>
#include <unistd.h>

//#include <nlohmann/json.hpp>

#include "demoapp.h"

#if 0
using std::literals::string_literals::operator""s;
using std::shared_ptr;
using std::string;
using std::string_view;
using std::vector;
using vecstringptr = std::shared_ptr<std::vector<std::string>>;
using DbWriterNS::DbWriter;
using DbWriterNS::DbWriterGroup;
using DbWriterNS::DbWriterState;
using nlohmann::json;
using std::atomic_bool;
using std::atomic_int;
using std::make_shared;
using std::optional;
#endif

int main(int argc, char **argv) {
  DemoApp d;

  d.Run();

  return 0;
}
