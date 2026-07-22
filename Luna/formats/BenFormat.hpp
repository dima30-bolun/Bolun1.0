#pragma once
#include <cstdint>
#include <filesystem>
#include <string>
#include <vector>
namespace luna {
struct BenExecutable { std::string name; std::vector<std::uint8_t> payload; std::string entry; };
class BenFormat { public: static bool write(const std::filesystem::path& path, const BenExecutable& exe); static BenExecutable read(const std::filesystem::path& path); static bool run(const BenExecutable& exe, std::string& output); };
}
