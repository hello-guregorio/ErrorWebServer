#include <mysql_pool.hh>

int main() {
    sql_instance.init("../cfg/db_info.json");
    auto test=sql_instance.get_conn();
    sql_instance.give_back(test);
    sql_instance.get_conn();
    sql_instance.get_conn();
    sql_instance.get_conn();
}
