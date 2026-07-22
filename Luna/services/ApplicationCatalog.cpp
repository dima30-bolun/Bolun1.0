#include "ApplicationCatalog.hpp"
#include <algorithm>
namespace luna {
void ApplicationCatalog::add(ApplicationInfo app){ if(!app.id.empty()) apps_.push_back(std::move(app)); }
std::vector<ApplicationInfo> ApplicationCatalog::all() const { return apps_; }
std::vector<ApplicationInfo> ApplicationCatalog::search(const std::string& query) const { std::vector<ApplicationInfo> out; for(const auto& a:apps_) if(a.name.find(query)!=std::string::npos || a.id.find(query)!=std::string::npos) out.push_back(a); return out; }
}
