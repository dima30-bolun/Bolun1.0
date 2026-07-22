#include "Logger.hpp"
#include <chrono>
#include <iomanip>
namespace luna {
Logger::Logger(std::filesystem::path root) : root_(std::move(root)) { std::filesystem::create_directories(root_); }
std::filesystem::path Logger::fileFor(const std::string& subsystem) const { return root_ / (subsystem + ".log"); }
bool Logger::write(const std::string& subsystem, const std::string& level, const std::string& message) {
  std::lock_guard<std::mutex> lock(mutex_);
  std::filesystem::create_directories(root_);
  std::ofstream out(fileFor(subsystem), std::ios::app);
  if (!out) return false;
  const auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
  out << std::put_time(std::gmtime(&now), "%FT%TZ") << ' ' << level << ' ' << message << '\n';
  return static_cast<bool>(out);
}
}
