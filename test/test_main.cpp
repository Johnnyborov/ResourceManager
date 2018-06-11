#include <iostream>
#include "ResourceHandle.h"

int main() {
  ResourceHandle rh1("qwerty");
  ResourceHandle rh2("test_resource.txt");

  std::cout << rh2.c_str();

  std::cin.get();
  return 0;
}