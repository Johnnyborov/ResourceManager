#include <fstream>
#include <string>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

int main(int argc, char* argv[]) {
  std::ofstream ofs_confing{ "resources_config.cpp" };

  if (std::string(argv[1]) == "-start" || std::string(argv[1]) == "-both") {
    ofs_confing <<
      "#include \"ResourceHandle.h\"\n"
      "\n"
      "ResourceHandle::ResourceHandle(std::string resource_name) {\n"
      "  ";
  }

  fs::path input_file_path{ argv[2] }; 
  std::string input_file_name = input_file_path.filename().string();

  std::string original_input_file_name = input_file_name;
  std::replace(input_file_name.begin(), input_file_name.end(), '-', '_');
  std::replace(input_file_name.begin(), input_file_name.end(), '.', '_');

  std::ifstream ifs{ argv[2] };
  std::ofstream ofs{ argv[3] };

  ofs << "#include <cstddef>\n";
  ofs << "extern const char _resource_" << input_file_name << "_data[] = {\n";

  int line_count = 0;
  char c;
  while (ifs.get(c)) {
    ofs << "0x" << std::hex << (c & 0xff) << ", ";

    if (++line_count == 10) {
      ofs << '\n';
      line_count = 0;
    }
  }

  ofs << "\'\\0\'"; // null terminator in case data is going to be treated as c string
  ofs << "};\n";
  ofs << "extern const size_t _resource_" << input_file_name << "_len = sizeof(_resource_" << input_file_name << "_data) - 1;\n";


  ofs_confing <<
    "if (resource_name == \"" << original_input_file_name << "\") {\n"
    "    extern const char _resource_" << input_file_name << "_data[];\n"
    "    extern const size_t _resource_" << input_file_name << "_len;\n"
    "    m_data_start = _resource_" << input_file_name << "_data;\n"
    "    m_data_len = _resource_" << input_file_name << "_len;\n"
    "  } else ";

  if (std::string(argv[1]) == "-end" || std::string(argv[1]) == "-both") {
    ofs_confing <<
      "{\n"
      "    fprintf(stdout, \"Error: resource not found\\n\");\n"
      "  }\n"
      "}\n";
  }
    
  return 0;
}