#include "BappPackage.hpp"
#include <fstream>
#include <sstream>
namespace luna {
std::string BappPackage::sign(const BappManifest& m){ return std::to_string(std::hash<std::string>{}(m.id + m.name + m.executable)); }
bool BappPackage::saveManifest(const std::filesystem::path& file, const BappManifest& m){ std::filesystem::create_directories(file.parent_path()); std::ofstream out(file); if(!out) return false; out << "id="<<m.id<<"\nname="<<m.name<<"\nexecutable="<<m.executable<<"\nsignature="<<(m.signature.empty()?sign(m):m.signature)<<"\n"; for(const auto& l:m.locales) out << "locale."<<l.first<<'='<<l.second<<"\n"; return static_cast<bool>(out); }
BappManifest BappPackage::loadManifest(const std::filesystem::path& file){ BappManifest m; std::ifstream in(file); std::string line; while(std::getline(in,line)){ auto p=line.find('='); if(p==std::string::npos) continue; auto k=line.substr(0,p); auto v=line.substr(p+1); if(k=="id") m.id=v; else if(k=="name") m.name=v; else if(k=="executable") m.executable=v; else if(k=="signature") m.signature=v; else if(k.rfind("locale.",0)==0) m.locales[k.substr(7)]=v; } return m; }
}
