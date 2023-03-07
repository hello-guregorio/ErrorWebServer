#include <mysql_pool.hh>

int main() {
    mysql_pool::get_instance().init(const char *host, int port, const char *user, const char *pwd, const char *db_name)
}
