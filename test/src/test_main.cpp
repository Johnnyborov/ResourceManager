// Copyright (c) 2018 Johnny Borov <JohnnyBorov@gmail.com>. Released under MIT License.

#include <iostream>
#include "ResourceManager/ResourceHandle.h"

void testInvalidResource() {
  ResourceHandle rhdi("i_dont_exist"); // -DRM_NO_EXCEPTIONS to disable throw on invalid recource
  std::cout << "rhdi is valid = " << rhdi.isValid() << '\n';
}

int main() {
  try {
    ResourceHandle rh1("res.txt");
    ResourceHandle rh2("res2.txt");
    std::cout << "rh1 c_str = " << rh1.c_str() << '\n';
    std::cout << "rh2 string = " << rh2.string() << '\n';

    ResourceHandle rh3("resources/res.txt");
    std::cout << "rh3 is valid = " << rh3.isValid() << '\n';
    std::cout << "rh3 data = " << rh3.data() << '\n';
    std::cout << "rh3 size = " << rh3.size() << '\n';

    testInvalidResource();
  } catch (const ResourceNotFound& e) {
    std::cout << e.what() << '\n';
  }

  std::cin.get();
  return 0;
}