#pragma once
#include <filesystem>
#include <string>
#include <vector>
namespace luna {
struct Resource { std::string type; std::filesystem::path path; };
class ResourceIndex { public: explicit ResourceIndex(std::filesystem::path root); std::vector<Resource> scan() const; private: std::filesystem::path root_; };
}
