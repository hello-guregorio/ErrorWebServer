#ifndef SAFE_QUEUE_H
#define SAFE_QUEUE_H

#include "noncopyable.hh"
#include <chrono>
#include <condition_variable>
#include <deque>
#include <mutex>
#include <utility>
template <typename T> class safe_queue : noncopyable {
  using unique_lock = std::unique_lock<std::mutex>;

public:
  safe_queue() = default;
  template <typename obj_T> void push(obj_T &&obj);
  bool pop(T &obj, int timeout = 0);
  auto size() const {
    unique_lock locker(m_mtx);
    return m_deque.size();
  }
  bool empty() const {
    unique_lock locker(m_mtx);
    return m_deque.empty();
  }
  void clear() {
    unique_lock locker(m_mtx);
    m_deque.clear();
  }

private:
  std::deque<T> m_deque;
  mutable std::mutex m_mtx;
  std::condition_variable m_cond;
};

template <typename T>
template <typename obj_T>
void safe_queue<T>::push(obj_T &&obj) {
  {
    unique_lock locker(m_mtx);
    m_deque.push_back(std::forward<obj_T>(obj));
  }
  m_cond.notify_one();
}
template <typename T> bool safe_queue<T>::pop(T &obj, int timeout) {
  unique_lock locker(m_mtx);
  if (timeout <= 0) {
    m_cond.wait(locker, [this] { return !m_deque.empty(); });
    obj = std::move(m_deque.front());
    m_deque.pop_front();
    return true;
  } else {
    using ms = std::chrono::milliseconds;
    //成功才移动
    if (m_cond.wait_for(locker, ms(timeout),
                        [this] { return !m_deque.empty(); })) {
      obj = std::move(m_deque.front());
      m_deque.pop_front();
      return true;
    }
  }
  return false;
}

#endif