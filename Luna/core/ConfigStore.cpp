#include "ConfigStore.hpp"
#include <fstream>
namespace luna {
ConfigStore::ConfigStore(std::filesystem::path file) : file_(std::move(file)) {}
bool ConfigStore::load() {
  values_.clear();
  std::ifstream in(file_);
  if (!in) return false;
  std::string line;
  while (std::getline(in, line)) {
    if (line.empty() || line[0] == '#') continue;
    const auto pos = line.find('=');
    if (pos != std::string::npos) values_[line.substr(0, pos)] = line.substr(pos + 1);
  }
  return true;
}
bool ConfigStore::save() const {
  std::filesystem::create_directories(file_.parent_path());
  std::ofstream out(file_);
  if (!out) return false;
  for (const auto& item : values_) out << item.first << '=' << item.second << '\n';
  return static_cast<bool>(out);
}
void ConfigStore::set(std::string key, std::string value) { values_[std::move(key)] = std::move(value); }
std::string ConfigStore::get(const std::string& key, const std::string& fallback) const { auto it = values_.find(key); return it == values_.end() ? fallback : it->second; }
const std::map<std::string,std::string>& ConfigStore::values() const { return values_; }
}
