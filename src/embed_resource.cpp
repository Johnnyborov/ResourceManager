#include <fstream>
#include <string>

std::string modifyFileName(std::string file_name) {
  size_t search_from_pos = 0;
  size_t replace_from_pos;
   while ((replace_from_pos = file_name.find_first_of(".- /\\", search_from_pos)) != std::string::npos) {
     switch (file_name[replace_from_pos]) {
     case '.':
       file_name.replace(replace_from_pos, 1, "__dot__");
       search_from_pos = replace_from_pos + 7; // shift len(__dot__) = 7 symbols
       break;
     case '-':
       file_name.replace(replace_from_pos, 1, "__dash__");
       search_from_pos = replace_from_pos + 8;
       break;
     case ' ':
       file_name.replace(replace_from_pos, 1, "__space__");
       search_from_pos = replace_from_pos + 9;
       break;
     case '/':
       file_name.replace(replace_from_pos, 1, "__slash__");
       search_from_pos = replace_from_pos + 9;
       break;
     case '\\':
       file_name.replace(replace_from_pos, 1, "__bslash__");
       search_from_pos = replace_from_pos + 10;
       break;
     }
  }

  return file_name;
}

int main(int argc, char* argv[]) {
  if (std::string(argv[1]) == "-data") {
    std::string input_file_name{ argv[3] };

    std::string modified_input_file_name = modifyFileName(input_file_name);

    std::ifstream ifs{ argv[2], std::ios::binary };
    std::ofstream ofs{ argv[4] };

    ofs << "#include <cstddef>\n";
    ofs << "extern const char _resource_" << modified_input_file_name << "_data[] = {\n";

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
    ofs << "extern const size_t _resource_" << modified_input_file_name <<
    "_len = sizeof(_resource_" << modified_input_file_name << "_data) - 1;\n";
  } else if (std::string(argv[1]) == "-config") {
    std::ofstream ofs_confing("__resources__config.cpp");

    ofs_confing <<
      "#include \"ResourceManager/ResourceHandle.h\"\n"
      "\n"
      "ResourceHandle::ResourceHandle(std::string resource_name) {\n"
      "  ";

    if (argc == 3) {
      std::string files_list{argv[2]};

      size_t length = files_list.length();
      size_t start_pos = 0;
      do {
        size_t end_pos = files_list.find_first_of(';', start_pos);
        if (end_pos == std::string::npos)
          end_pos = length;

        std::string input_file_name = files_list.substr(start_pos, end_pos - start_pos);

        std::string modified_input_file_name = modifyFileName(input_file_name);
        ofs_confing <<
          "if (resource_name == \"" << input_file_name << "\") {\n"
          "    extern const char _resource_" << modified_input_file_name << "_data[];\n"
          "    extern const size_t _resource_" << modified_input_file_name << "_len;\n"
          "    m_data_start = _resource_" << modified_input_file_name << "_data;\n"
          "    m_data_len = _resource_" << modified_input_file_name << "_len;\n"
          "  } else ";

        start_pos = end_pos + 1;
      } while (start_pos < length);
    }

    ofs_confing <<
      "{\n"
      "#ifdef RM_NO_EXCEPTIONS\n"
      "    m_data_start = nullptr;\n"
      "    m_data_len = 0;\n"
      "#else\n"
      "    throw ResourceNotFound{resource_name};\n"
      "#endif\n"
      "  }\n"
      "}\n";
  }

  return 0;
}