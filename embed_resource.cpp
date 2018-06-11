#include <fstream>
int main(int argc, char* argv[]) {

  std::ofstream ofs{ argv[1] };
  ofs <<
    "#include \"ResourceHandle.h\"\n"
    "\n"
    "ResourceHandle::ResourceHandle(std::string resource_name) {\n"
    "  if (resource_name == \"qwerty\") {\n"
    "    fprintf(stdout, \"qwerty\");\n"
    "  }\n"
    "\n"
    "}\n";


  return 0;
}