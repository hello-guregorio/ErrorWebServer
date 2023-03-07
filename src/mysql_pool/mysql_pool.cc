#include <mysql_pool.hh>
mysql_pool &mysql_pool::get_instance() {
  static mysql_pool instance;
  return instance;
}

void mysql_pool::init(const char *host, int port, const char *user,
                      const char *pwd, const char *db_name, int conn_size) {
  assert(conn_size > 0);
  for (int i = 0; i < conn_size; ++i) {
    MYSQL *sql = nullptr;
    sql = mysql_init(sql);
    if (sql == nullptr) {
      // log
      assert(sql);
    }
    sql = mysql_real_connect(sql, host, user, pwd, db_name, port, nullptr, 0);
    if(sql==nullptr){
        //log
    }
  }
}