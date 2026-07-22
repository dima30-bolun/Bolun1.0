#pragma once
#include <filesystem>
#include <map>
#include <string>
namespace luna { struct BappManifest { std::string id; std::string name; std::string executable; std::string signature; std::map<std::string,std::string> locales; }; class BappPackage { public: static bool saveManifest(const std::filesystem::path& file, const BappManifest& m); static BappManifest loadManifest(const std::filesystem::path& file); static std::string sign(const BappManifest& m); }; }
