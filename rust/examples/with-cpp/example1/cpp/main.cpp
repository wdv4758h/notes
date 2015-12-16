#include <cstdint>
#include <iostream>

extern "C" {
  uint32_t add(uint32_t lhs, uint32_t rhs);
}

int main() {
  std::cout << "1300 + 14 == " << add(1300, 14) << '\n';
  return 0;
}
