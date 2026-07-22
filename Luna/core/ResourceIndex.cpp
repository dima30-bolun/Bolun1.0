#include "ResourceIndex.hpp"
namespace luna {
ResourceIndex::ResourceIndex(std::filesystem::path root) : root_(std::move(root)) {}
std::vector<Resource> ResourceIndex::scan() const {
  std::vector<Resource> items;
  if (!std::filesystem::exists(root_)) return items;
  for (const auto& entry : std::filesystem::recursive_directory_iterator(root_)) {
    if (!entry.is_regular_file()) continue;
    auto ext = entry.path().extension().string();
    if (!ext.empty() && ext[0] == '.') ext.erase(0,1);
    items.push_back({ext, entry.path()});
  }
  return items;
}
}
