#include "LunaProject.hpp"
#include <fstream>
namespace luna {
bool LunaProject::write(const std::filesystem::path& file, const LunaProjectSpec& spec){ std::filesystem::create_directories(file.parent_path()); std::ofstream out(file); if(!out) return false; out << "name="<<spec.name<<"\nversion="<<spec.version<<"\n"; for(const auto& s:spec.sources) out << "source="<<s<<"\n"; return static_cast<bool>(out); }
LunaProjectSpec LunaProject::read(const std::filesystem::path& file){ LunaProjectSpec spec; std::ifstream in(file); std::string line; while(std::getline(in,line)){ auto p=line.find('='); if(p==std::string::npos) continue; auto k=line.substr(0,p); auto v=line.substr(p+1); if(k=="name") spec.name=v; else if(k=="version") spec.version=v; else if(k=="source") spec.sources.push_back(v); } return spec; }
}
