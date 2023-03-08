#ifndef MYSQL_POOL_H
#define MYSQL_POOL_H

#include "noncopyable.hh"
#include "parse_cfg.hh"
#include <memory>
#include <mysql/mysql.h>
#include <safe_queue.hh>
using ptr_MYSQL = std::shared_ptr<MYSQL>;

class mysql_pool : noncopyable {
public:
  static mysql_pool &get_instance();
  void init(const std::string& file_path);

private:
  mysql_pool() = default;
  safe_queue<ptr_MYSQL> m_pool;
  parse_db_cfg db_cfg;
};
#define sql_instance mysql_pool::get_instance()

#endif