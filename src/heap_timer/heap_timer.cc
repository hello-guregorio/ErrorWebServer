#include <heap_timer.hh>
#include <memory>

void heap_timer::percolate_up(int i) {
  assert(i >= 0 && i < m_heap.size());
  int father = (i - 1) >> 2;
  auto copy = std::move(m_heap[i]);
  while (father >= 0) {
    if (*(m_heap[father]) < *copy) {
      break;
    }
    m_heap[i] = std::move(m_heap[father]);
    i = father;
    father = (i - 1) >> 2;
  }
  m_heap[i] = std::move(copy);
}

bool heap_timer::percolate_down(int i, int n) {
  assert(i >= 0 && i < m_heap.size());
  assert(n >= 0 && n <= m_heap.size());
  int child = 2 * i + 1;
  while (child < n) {
    //取最大的孩子
    if (child + 1 < n && *(m_heap[child + 1]) < *(m_heap[child])) {
      ++child;
    }
  }
}

void heap_timer::add(int id, int timeout, const timeout_callback &cb_func) {
  assert(id >= 0);
  int i;
  if (m_dict[id] == 0) {
    i = m_heap.size();
    m_dict[id] = i;
    auto new_node = std::make_unique<timer_node>();
    new_node->id = id;
    new_node->expires = hr_clock::now() + ms(timeout);
    new_node->cb_func = cb_func;
    m_heap.emplace_back(new_node);
    percolate_up(i);
  } else {
    i = m_dict[id];
    m_heap[i]->expires = hr_clock::now() + ms(timeout);
    m_heap[i]->cb_func = cb_func;
    if (!percolate_down(i, m_heap.size())) {
      percolate_up(i);
    }
  }
}
