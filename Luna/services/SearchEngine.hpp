#pragma once
#include "ApplicationCatalog.hpp"
namespace luna { class SearchEngine { public: explicit SearchEngine(const ApplicationCatalog& catalog); std::vector<ApplicationInfo> applications(const std::string& query) const; private: const ApplicationCatalog& catalog_; }; }
