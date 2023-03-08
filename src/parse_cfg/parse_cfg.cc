#include <fstream>
#include <parse_cfg.hh>
void parse_db_cfg::load(const std::string &file_name) {
  json j;
  std::ifstream db_cfg_file(file_name);
  db_cfg_file >> j;
  host = j["host"];
  port = j["port"];
  user = j["user"];
  pwd = j["pwd"];
  db_name = j["db_name"];
  max_size = j["max_size"];
}