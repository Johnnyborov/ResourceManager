#include <fstream>
#include <string>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

int main(int argc, char* argv[]) {
  if (std::string(argv[1]) == "-data") {
    fs::path input_file_path{ argv[2] }; 
    std::string input_file_name = input_file_path.filename().string();

    std::replace(input_file_name.begin(), input_file_name.end(), '-', '_');
    std::replace(input_file_name.begin(), input_file_name.end(), '.', '_');

    std::ifstream ifs{ argv[2], std::ios::binary };
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

    ofs << "\'\\0\'"; // null terminator in case data is going to be interprited as a c string
    ofs << "};\n";
    ofs << "extern const size_t _resource_" << input_file_name << "_len = sizeof(_resource_" << input_file_name << "_data) - 1;\n";
  } else if (std::string(argv[1]) == "-config") {
    std::ofstream ofs_confing("resources_config.cpp");

    ofs_confing <<
      "#include \"ResourceHandle.h\"\n"
      "\n"
      "ResourceHandle::ResourceHandle(std::string resource_name) {\n"
      "  ";


    std::string files_list{argv[2]};

    int length = files_list.length();
    int start_pos = 0;
    do {
      int end_pos = files_list.find_first_of(';', start_pos);
      if (end_pos == std::string::npos)
        end_pos = length;

      std::string file_path = files_list.substr(start_pos, end_pos - start_pos);

      fs::path input_file_path{ file_path }; 
      std::string input_file_name = input_file_path.filename().string();

      std::string original_input_file_name = input_file_name;
      std::replace(input_file_name.begin(), input_file_name.end(), '-', '_');
      std::replace(input_file_name.begin(), input_file_name.end(), '.', '_');

      ofs_confing <<
        "if (resource_name == \"" << original_input_file_name << "\") {\n"
        "    extern const char _resource_" << input_file_name << "_data[];\n"
        "    extern const size_t _resource_" << input_file_name << "_len;\n"
        "    m_data_start = _resource_" << input_file_name << "_data;\n"
        "    m_data_len = _resource_" << input_file_name << "_len;\n"
        "  } else ";

      start_pos = end_pos + 1;
    } while (start_pos < length);


    ofs_confing <<
      "{\n"
      "    fprintf(stdout, \"Error: resource not found\\n\");\n"
      "  }\n"
      "}\n";
  }

  return 0;
}