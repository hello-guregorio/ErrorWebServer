#ifndef PARSE_CFG_H
#define PARSE_CFG_H
#include "json.hpp"
#include <fstream>
#include <iostream>
using json = nlohmann::json;

class parse_cfg {
public:
  virtual void load(const std::string &file_name) = 0;
};

class parse_db_cfg : public parse_cfg {
private:
  friend class mysql_pool;
  std::string host;
  int port;
  std::string user;
  std::string pwd;
  std::string db_name;
  int max_size;

public:
  void load(const std::string &file_name) override;
};

#endif