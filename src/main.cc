#include <iostream>
#include <random>
#include <ring_buffer.hh>
int main() {
  ring_buffer test(4096);
  std::default_random_engine re;
  std::uniform_int_distribution<int> dis(0, 99);
  std::uniform_int_distribution<int> dis1(0, 25);
  int count = 0;
  for (int j = 0; j < 1000; ++j) {
    std::string str;
    for (int i = 0; i < dis(re); ++i) {
      char c=dis1(re)+'a';
      str.push_back(c);
    }
    if (dis(re) < 50) {
      if (test.write_available() > str.size()) {
        count += str.size();
        test.append(str);
      }
    } else {
      if (test.read_available() > str.size()) {
        count -= str.size();
        test.remove(str, str.size());
      }
    }
  }
  std::cout << count << std::endl;
  std::cout << test.read_available() << std::endl;
}
