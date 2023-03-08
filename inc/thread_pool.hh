#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include "noncopyable.hh"
#include <atomic>
#include <condition_variable>
#include <functional>
#include <future>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>
class thread_pool : noncopyable {
  using ul_lock = std::unique_lock<std::mutex>;
  using Task = std::function<void()>;
  std::vector<std::thread> workers; //线程池
  std::queue<Task> tasks;           //任务队列

  // sync
  std::atomic<bool> stop;       //是否停止
  std::atomic<int> running_num; //线程运行数
  std::mutex m_mtx;
  std::condition_variable m_cond;

public:
  explicit thread_pool(int thread_count = 8);
  ~thread_pool();
  template <typename func_Type, class... Args>
  auto enqueue(func_Type &&func, Args &&...args);
  void add_thread(int size);
};

int hello(int a, int b);

// 完美转发
template <typename func_Type, class... Args>
auto thread_pool::enqueue(func_Type &&func, Args &&...args) {
  using ret_type = decltype(func(args...));
  auto task = std::make_shared<std::packaged_task<ret_type()>>(
      std::bind(std::forward<func_Type>(func), std::forward<Args>(args)...));
  std::future<ret_type> res = task->get_future();
  {
    ul_lock locker(m_mtx);
    tasks.emplace([task] { (*task)(); });
  }
  m_cond.notify_one();
  return res;
}

#endif