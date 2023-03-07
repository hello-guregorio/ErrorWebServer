#ifndef NONCOPYABLE_H
#define NONCOPYABLE_H

class noncopyable {
  noncopyable(const noncopyable &) = delete;
  void operator=(const noncopyable &) = delete;

protected:
  noncopyable() = default;
  ~noncopyable() = default;
};

#endif