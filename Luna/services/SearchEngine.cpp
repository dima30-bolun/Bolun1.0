#include "SearchEngine.hpp"
namespace luna { SearchEngine::SearchEngine(const ApplicationCatalog& catalog):catalog_(catalog){} std::vector<ApplicationInfo> SearchEngine::applications(const std::string& query) const { return catalog_.search(query); } }
