#ifndef BOO_INI_READER_HPP
#define BOO_INI_READER_HPP
#include <fstream>
#include <regex>
#include <string>
#include <unordered_map>

namespace iboo9x {
class IniReader
{
public:
  // Contructor
  IniReader(std::string aFileName = "");
  // Mutators
  /**
   * @brief Set new ini file name
   *
   * @param aFileName new ini file name
   */
  void SetFileName(std::string aFileName);
  /**
   * @brief Load ini data to database
   *
   */
  void FetchData();
  /**
   * @brief Clear database
   *
   */
  void Clear();
  // Accessors
  /**
   * @brief Get value from a key
   *
   * @param aSection section
   * @param aKey key
   * @return std::string
   */
  const std::string& GetVal(std::string aSection, std::string aKey) const;
  /**
   * @brief Get all key-val pairs in a section
   *
   * @param aSection
   * @return std::unordered_map<std::string, std::string>
   */
  const std::unordered_map<std::string, std::string>& GetWholeSection(
    std::string aSection) const;

private:
  std::string mFileName;
  std::unordered_map<std::string, std::unordered_map<std::string, std::string>>
    mDatabase;
};
}
#endif // BOO_INI_READER_HPP