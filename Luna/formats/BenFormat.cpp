#include "BenFormat.hpp"
#include <fstream>
namespace luna {
static void putString(std::ofstream& out, const std::string& text){ std::uint32_t n=static_cast<std::uint32_t>(text.size()); out.write(reinterpret_cast<const char*>(&n),4); out.write(text.data(), static_cast<std::streamsize>(text.size())); }
static bool getString(std::ifstream& in, std::string& text){ std::uint32_t n=0; in.read(reinterpret_cast<char*>(&n),4); if(!in) return false; text.assign(n,'\0'); in.read(text.data(), static_cast<std::streamsize>(n)); return static_cast<bool>(in); }
bool BenFormat::write(const std::filesystem::path& path, const BenExecutable& exe){ std::ofstream out(path, std::ios::binary); if(!out) return false; out.write("BEN1",4); putString(out, exe.name); putString(out, exe.entry); std::uint32_t n=static_cast<std::uint32_t>(exe.payload.size()); out.write(reinterpret_cast<const char*>(&n),4); out.write(reinterpret_cast<const char*>(exe.payload.data()), static_cast<std::streamsize>(exe.payload.size())); return static_cast<bool>(out); }
BenExecutable BenFormat::read(const std::filesystem::path& path){ BenExecutable exe; std::ifstream in(path, std::ios::binary); char magic[4]{}; in.read(magic,4); if(std::string(magic,4)!="BEN1") return exe; getString(in, exe.name); getString(in, exe.entry); std::uint32_t n=0; in.read(reinterpret_cast<char*>(&n),4); exe.payload.resize(n); in.read(reinterpret_cast<char*>(exe.payload.data()), static_cast<std::streamsize>(n)); return exe; }
bool BenFormat::run(const BenExecutable& exe, std::string& output){ if(exe.name.empty() || exe.entry.empty()) return false; output = "Luna Runtime executed " + exe.name + " via " + exe.entry + " with " + std::to_string(exe.payload.size()) + " bytes"; return true; }
}
