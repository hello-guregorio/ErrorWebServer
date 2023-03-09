#ifndef RING_BUFFER_H
#define RING_BUFFER_H
#include <memory>
#include <string>
//浪费一个字节的实现方案
class ring_buffer {
  std::unique_ptr<char[]> buffer;
  int start_pos;
  int end_pos;
  int size;

public:
  ring_buffer(int size = 4096)
      : buffer(std::make_unique<char[]>(size + 1)), start_pos(0), end_pos(0),
        size(size) {}
  bool empty() const { return start_pos == end_pos; }
  bool full() const { return (end_pos + 1) % size==start_pos; }
  int read_available() const {
    if (end_pos >= start_pos) {
      return end_pos - start_pos;
    } else {
      return size - start_pos + end_pos;
    }
  }
  int write_available() const { return size - read_available(); }
  //添加一个字符,成功true,失败false
  bool append(char ch) {
    if (!full()) {
      buffer[end_pos] = ch;
      end_pos = (end_pos + 1) % size;
      return true;
    }
    return false;
  }
  //返回添加的字节个数
  int append(const char *data, int len) {
    int i = 0;
    while (!full()&&i<len) {
      buffer[end_pos] = data[i++];
      end_pos = (end_pos + 1) % size;
    }
    return i;
  }
  int append(const std::string &data) {
    return append(data.c_str(), data.size());
  }

  bool remove(char &ch) {
    if (!empty()) {
      ch = buffer[start_pos];
      start_pos = (start_pos + 1) % size;
      return true;
    }
    return false;
  }
  //给dst传字节
  int remove(char *dst, int len) {
    int i = 0;
    while (!empty()&&i<len) {
      dst[i++] = buffer[start_pos];
      start_pos = (start_pos + 1) % size;
    }
    return i;
  }
  int remove(std::string &dst, int len) {
    int i = 0;
    while (!empty()&&i<len) {
      ++i;
      dst.push_back(buffer[start_pos]);
      start_pos = (start_pos + 1) % size;
    }
    return i;
  }
};

#endif