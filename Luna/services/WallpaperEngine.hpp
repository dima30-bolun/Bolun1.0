#pragma once
#include <filesystem>
#include <vector>
namespace luna { class WallpaperEngine { public: void add(std::filesystem::path path); std::filesystem::path current() const; std::filesystem::path next(); private: std::vector<std::filesystem::path> slides_; unsigned index_=0; }; }
