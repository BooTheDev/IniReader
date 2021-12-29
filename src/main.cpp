#include "ini_reader.hpp"
#include <iostream>
using namespace iboo9x;

int
main()
{
  try {
    IniReader ini("sample.ini");
    ini.FetchData();
    std::string section("FTP");
    auto data = ini.GetWholeSection(section);

    if (!data.empty()) {
      std::cout << '[' << section << ']' << std::endl;
      for (auto& p : data) {
        std::cout << p.first << "=" << p.second << std::endl;
      }
    }
  } catch (const std::runtime_error& e) {
    std::cout << e.what() << std::endl;
    return 1;
  }

  return 0;
}