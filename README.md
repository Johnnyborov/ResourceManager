# ResourceManager
ResourceManager is a light cross-platform C++ CMake library to embed resources into executables or libraries.
Light and cross-platform here means that it only depends on C++ standard library and CMake and doesn't use anything system specific.
Any type of resource files is possible for embedding (text files or binary files like images or any other data).

It's based on compiling binary representation of resource files into C++ global byte array and provides easy and convenient means
to access this array from C++ code.

# To use ResourceManager
1) Add it as a subdirectory into your project:
```
add_subdirectory("path to ResourceManager")
```
2) Include its include directory (RESOURCE_MANAGER_INCLUDE_DIRS is defined after you add subdirectory):
```
include_directories(${RESOURCE_MANAGER_INCLUDE_DIRS})
```
3) Run rm_embed_resources command defined in subdirectory to generate source files containing resource files data:
```
rm_embed_resources(RESOURCES "res.txt" "src/main.cpp" "images/myimage.png")
```
4) Use the now defined RESOURCES list-variable to add those source into your executable/library:
```
add_executable(MyProject src/main.cpp ${RESOURCES})
```
5) Include the header into your C++ code:
```
#include "ResourceManager/ResourceHandle.h"
```
6) You can now use ResourceHandle class to access the resources binary data from C++:
```
ResourceHandle resource_handle("res.txt");
std::cout << "res.txt contents: " << resource_handle.c_str() << '\n';
std::cout << "res.txt length: " << resource_handle.length() << '\n';
ResourceHandle code_of_main_cpp("src/main.cpp");
std::cout << "source code of main.cpp:\n" << code_of_main_cpp.string() << '\n';
ResourceHandle my_image("images/myimage.png");
doSomethingWithBinaryDataOfMyImage(my_image.data(), my_image.size());
```

# Additional information
In the test forlder of this repository there is a simple cmake project which you can use as an example:
[CMakeLists.txt](test/CMakeLists.txt) [test_main.cpp](test/src/test_main.cpp)

More information about ResourceHandle class usage is avaliable in its header
[ResourceHandle.h](include/ResourceManager/ResourceHandle.h)

# Author
Johnny Borov JohnnyBorov@gmail.com

# Licence
MIT License. See [LICENSE](LICENSE) file.
