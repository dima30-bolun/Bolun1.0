#pragma once
#include <filesystem>
#include <string>
#include <vector>
namespace luna { struct LunaProjectSpec { std::string name; std::string version; std::vector<std::string> sources; }; class LunaProject { public: static bool write(const std::filesystem::path& file, const LunaProjectSpec& spec); static LunaProjectSpec read(const std::filesystem::path& file); }; }
