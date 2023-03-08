#include <mariadb/mysql.h>
#include <mysql_pool.hh>

mysql_pool &mysql_pool::get_instance() {
  // c++11后静态变量初始化线程安全,且局部
  //静态变量可以在第一次调用才构造
  static mysql_pool instance;
  return instance;
}

void mysql_pool::init(const std::string &file_path) {
  db_cfg.load(file_path);
  for (int i = 0; i < db_cfg.max_size; ++i) {
    MYSQL *sql = nullptr;
    sql = mysql_init(sql);
    if (!sql) {
      // log
      assert(sql);
    }
    sql = mysql_real_connect(sql, db_cfg.host.c_str(), db_cfg.user.c_str(),
                             db_cfg.pwd.c_str(), db_cfg.db_name.c_str(),
                             db_cfg.port, nullptr, 0);
    if (!sql) {
      // log error
    }
    //一定要mysql_close!!!,一下子泄露80mb内存太顶了
    //已经用valgrind检测过了,没泄露了
    m_pool.push(ptr_MYSQL(sql, [](MYSQL *sql) { 
      mysql_close(sql); }));
  }
}

ptr_MYSQL mysql_pool::get_conn() {
  ptr_MYSQL conn=nullptr;
  m_pool.pop(conn);
  return conn;
}

void mysql_pool::give_back(ptr_MYSQL &conn){
  m_pool.push(std::move(conn));
}
