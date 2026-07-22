#pragma once
#include <string>
#include <vector>
namespace luna { struct ApplicationInfo { std::string id; std::string name; std::string command; std::string icon; }; class ApplicationCatalog { public: void add(ApplicationInfo app); std::vector<ApplicationInfo> all() const; std::vector<ApplicationInfo> search(const std::string& query) const; private: std::vector<ApplicationInfo> apps_; }; }
