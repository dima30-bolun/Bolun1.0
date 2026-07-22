#pragma once
#include <filesystem>
#include <fstream>
#include <mutex>
#include <string>
namespace luna {
class Logger {
public:
  explicit Logger(std::filesystem::path root);
  bool write(const std::string& subsystem, const std::string& level, const std::string& message);
  std::filesystem::path fileFor(const std::string& subsystem) const;
private:
  std::filesystem::path root_;
  mutable std::mutex mutex_;
};
}
