#include <parse_cfg.hh>
#include <fstream>
void test_json() {
  json tmp={
    {"db_user","unknown"},
    {"db_user_passwd","1asdg20h0"},
  };
  std::ofstream file("test.json");
  file.write(tmp.dump(4).c_str(),tmp.dump(4).size());
  file.close();
}