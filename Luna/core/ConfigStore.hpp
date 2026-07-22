#pragma once
#include <filesystem>
#include <map>
#include <string>
namespace luna {
class ConfigStore {
public:
  explicit ConfigStore(std::filesystem::path file);
  bool load();
  bool save() const;
  void set(std::string key, std::string value);
  std::string get(const std::string& key, const std::string& fallback = {}) const;
  const std::map<std::string,std::string>& values() const;
private:
  std::filesystem::path file_;
  std::map<std::string,std::string> values_;
};
}
