#include <mysql_pool.hh>
#include <spdlog/spdlog.h>

mysql_pool &mysql_pool::get_instance() {
  // c++11后静态变量初始化线程安全,且局部
  //静态变量可以在第一次调用才构造
  static mysql_pool instance;
  return instance;
}

void mysql_pool::init(const std::string& file_path) {
  db_cfg.load(file_path);
  for (int i = 0; i < db_cfg.max_size; ++i) {
    MYSQL *sql = nullptr;
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
    m_pool.push(ptr_MYSQL(sql));
  }
  spdlog::info("push complete");
}
