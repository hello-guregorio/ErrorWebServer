#include <chrono>
#include <gtest/gtest.h>
#include <safe_queue.hh>
#include <parse_cfg.hh>
#include <thread>
#include <mysql_pool.hh>
#include <thread_pool.hh>
TEST(safe_queue, push) {
  safe_queue<int> sq;
  sq.push(1);
  int a = 2;
  sq.push(a);
  EXPECT_EQ(sq.size(), 2);
  int b;
  sq.pop(b);
  EXPECT_EQ(sq.size(), 1);
  EXPECT_EQ(b, 1);
}

TEST(safe_queue, pop) {
  using namespace std;
  safe_queue<int> sq;

  thread producer([&]() {
    //this_thread::sleep_for(5s);
    std::cout<<"start producer"<<std::endl;
    for (int i = 0; i < 100; ++i) {
      sq.push(i);
    }
  });

  thread consumer1([&]() {
    //this_thread::sleep_for(2s);
    for (int i = 0; i < 50; ++i) {
      int a;
      sq.pop(a);
    }
  });

  thread consumer2([&]() {
    for (int i = 0; i < 50; ++i) {
      int a;
      sq.pop(a);
    }
  });
  EXPECT_EQ(sq.size(),0);
  consumer1.join();
  consumer2.join();
  producer.join();
}

TEST(parse_db_cfg,load){
  parse_db_cfg db_cfg;
  db_cfg.load("../cfg/db_info.json");
}

TEST(mysql_pool,init){
  sql_instance.init("../cfg/db_info.json");
  sql_instance.get_conn();
}

TEST(thread_pool,enqueue){
  thread_pool pool(4);
  std::vector<std::future<int>> results;
  for(int i=0;i<30;++i){
    results.emplace_back(
      pool.enqueue([i]{
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return i*i;
      })
    );
  }
  for(int i=0;i<30;++i){
    EXPECT_EQ(i*i,results[i].get());
  }
}
int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}