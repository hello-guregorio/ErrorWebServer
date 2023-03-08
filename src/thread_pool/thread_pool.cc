#include <thread_pool.hh>

thread_pool::~thread_pool() {
  stop = true;
  m_cond.notify_all();
  for (auto &worker : workers) {
    worker.join();
  }
}

thread_pool::thread_pool(int thread_count) : stop(false), running_num(0) {
  add_thread(thread_count);
}

void thread_pool::add_thread(int size) {
  for (int i = 0; i < size; ++i) {
    workers.emplace_back([this] {
      while (!stop) {
        Task task;
        //加锁取出
        {
          ul_lock locker(m_mtx);
          m_cond.wait(locker, [this] { return stop || !tasks.empty(); });
          if (stop && tasks.empty()) {
            return;
          }
          task=std::move(tasks.front());
          tasks.pop();
        }
        ++running_num;
        //开始执行任务
        task();
        --running_num;
      }
    });
  }
}