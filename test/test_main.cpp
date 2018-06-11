#include <iostream>
#include "ResourceHandle.h"

int main(int argc, char* argv[]) {
  ResourceHandle rh1("res1.txt");
  ResourceHandle rhq("qwerty");
  ResourceHandle rh2("res2.txt");

  std::cout << rh1.c_str() << '\n';
  std::cout << rh2.c_str() << '\n';

  std::cin.get();
  return 0;
}