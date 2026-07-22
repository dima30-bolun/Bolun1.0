#include "Theme.hpp"
#include <functional>
#include <iomanip>
#include <sstream>
namespace luna {
Theme defaultTheme() { return {"Luna Aurora", "#7c5cff", 0.72, 18}; }
Theme automaticThemeFromWallpaperName(const std::string& wallpaper) {
  const auto value = std::hash<std::string>{}(wallpaper);
  std::ostringstream color;
  color << '#' << std::hex << std::setw(6) << std::setfill('0') << (value & 0xffffffu);
  return {"Luna Auto", color.str(), 0.70 + static_cast<double>(value % 10) / 100.0, 18};
}
}
