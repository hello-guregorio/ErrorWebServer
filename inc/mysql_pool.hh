#ifndef MYSQL_POOL_H
#define MYSQL_POOL_H

#include "noncopyable.hh"
#include <mysql/mysql.h>
#include <cassert>
#include <queue>
class mysql_pool : noncopyable {
public:
  static mysql_pool &get_instance();
  void init(const char *host, int port, const char *user,
            const char *pwd, const char *db_name, int conn_size = 10);
  
private:
  mysql_pool();
  ~mysql_pool();
  std::queue<MYSQL *> conn_pool;
};

#endif