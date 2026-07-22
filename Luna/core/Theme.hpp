#pragma once
#include <string>
namespace luna {
struct Theme { std::string name; std::string accent; double acrylicOpacity; int cornerRadius; };
Theme defaultTheme();
Theme automaticThemeFromWallpaperName(const std::string& wallpaper);
}
