#ifndef HEAP_TIMER_H
#define HEAP_TIMER_H

#include "noncopyable.hh"
#include <cassert>
#include <chrono>
#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>

using timeout_callback = std::function<void()>;
using hr_clock = std::chrono::high_resolution_clock;
using ms = std::chrono::milliseconds;
using timestamp = hr_clock::time_point;

struct timer_node {
  int id;
  timestamp expires;
  timeout_callback cb_func;
  bool operator<(const timer_node &t) { return expires < t.expires; }
};

//小根堆
//用指针来节省空间
class heap_timer : noncopyable {
public:
  heap_timer() { m_heap.reserve(64); }
  void add(int id, int timeout, const timeout_callback &cb_func);

private:
  ~heap_timer();
  void percolate_up(int i);
  bool percolate_down(int i,int n);
  std::vector<std::unique_ptr<timer_node>> m_heap;
  std::unordered_map<int, int> m_dict;
};

#endif