#include "ini_reader.hpp"

namespace iboo9x {
IniReader::IniReader(std::string aFileName)
{
  SetFileName(aFileName);
}

void
IniReader::SetFileName(std::string aFileName)
{
  if (std::fstream(aFileName)) {
    mFileName = aFileName;
  } else {
    throw std::runtime_error("Error: Could not read file.");
  }
}

void
IniReader::FetchData()
{
  std::fstream ini_file(mFileName, std::ios::in);
  std::regex rSection(R"(^\s*\[\s*(\w+)\s*\]\s*$)");
  std::regex rKeyVal(R"(^\s*(\w+)\s*=\s*(.*\S)\s*$)");
  std::regex rComment(R"(^\s*#.*)");
  std::regex rBlank(R"(^\s*$)");
  std::smatch matches;
  std::string line;
  std::string section;
  std::string key;
  std::string val;

  // Default section
  section = "_";
  mDatabase[section] = {};
  auto section_data = mDatabase.find(section);

  // Fetch data
  while (!ini_file.eof()) {
    std::getline(ini_file, line);
    if (std::regex_match(line, rComment)) {
      // skip comment
    } else if (std::regex_match(line, rBlank)) {
      // skip blank
    } else if (std::regex_match(line, matches, rKeyVal) && matches.ready()) {
      section_data->second[matches[1]] = matches[2];
    } else if (std::regex_match(line, matches, rSection) && matches.ready()) {
      section = matches[1];
      mDatabase[section] = {};
      section_data = mDatabase.find(section);
    } else {
      // skip unknown
    }
  }
}

void
IniReader::Clear()
{
  mDatabase.clear();
}

const std::string&
IniReader::GetVal(std::string aSection, std::string aKey) const
{
  auto section_data = mDatabase.find(aSection);
  if (section_data != mDatabase.end()) {
    auto& section_umap = section_data->second;
    auto key_data = section_umap.find(aKey);
    if (key_data != section_umap.end()) {
      return key_data->second;
    }
  }
  return {};
}

const std::unordered_map<std::string, std::string>&
IniReader::GetWholeSection(std::string aSection) const
{
  auto section_data = mDatabase.find(aSection);
  if (section_data != mDatabase.end()) {
    return section_data->second;
  }
  return {};
}
}