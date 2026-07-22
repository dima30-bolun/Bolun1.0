#include <array>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace {
void appendU32(std::vector<std::uint8_t>& out, std::uint32_t value) {
  out.push_back(static_cast<std::uint8_t>((value >> 24) & 0xff));
  out.push_back(static_cast<std::uint8_t>((value >> 16) & 0xff));
  out.push_back(static_cast<std::uint8_t>((value >> 8) & 0xff));
  out.push_back(static_cast<std::uint8_t>(value & 0xff));
}

std::uint32_t crc32(const std::vector<std::uint8_t>& bytes) {
  std::uint32_t crc = 0xffffffffu;
  for (std::uint8_t byte : bytes) {
    crc ^= byte;
    for (int bit = 0; bit < 8; ++bit) {
      const std::uint32_t mask = 0u - (crc & 1u);
      crc = (crc >> 1u) ^ (0xedb88320u & mask);
    }
  }
  return ~crc;
}

std::uint32_t adler32(const std::vector<std::uint8_t>& bytes) {
  std::uint32_t a = 1;
  std::uint32_t b = 0;
  for (std::uint8_t byte : bytes) {
    a = (a + byte) % 65521u;
    b = (b + a) % 65521u;
  }
  return (b << 16u) | a;
}

void appendChunk(std::vector<std::uint8_t>& png, const std::array<char, 4>& type, const std::vector<std::uint8_t>& data) {
  appendU32(png, static_cast<std::uint32_t>(data.size()));
  std::vector<std::uint8_t> crcInput;
  for (char c : type) {
    png.push_back(static_cast<std::uint8_t>(c));
    crcInput.push_back(static_cast<std::uint8_t>(c));
  }
  png.insert(png.end(), data.begin(), data.end());
  crcInput.insert(crcInput.end(), data.begin(), data.end());
  appendU32(png, crc32(crcInput));
}

std::vector<std::uint8_t> zlibStore(const std::vector<std::uint8_t>& raw) {
  std::vector<std::uint8_t> out{0x78, 0x01};
  std::size_t offset = 0;
  while (offset < raw.size()) {
    const std::size_t remaining = raw.size() - offset;
    const std::uint16_t block = static_cast<std::uint16_t>(remaining > 65535u ? 65535u : remaining);
    const bool final = offset + block == raw.size();
    out.push_back(final ? 0x01 : 0x00);
    out.push_back(static_cast<std::uint8_t>(block & 0xffu));
    out.push_back(static_cast<std::uint8_t>((block >> 8u) & 0xffu));
    const std::uint16_t inverse = static_cast<std::uint16_t>(~block);
    out.push_back(static_cast<std::uint8_t>(inverse & 0xffu));
    out.push_back(static_cast<std::uint8_t>((inverse >> 8u) & 0xffu));
    out.insert(out.end(), raw.begin() + static_cast<std::ptrdiff_t>(offset), raw.begin() + static_cast<std::ptrdiff_t>(offset + block));
    offset += block;
  }
  appendU32(out, adler32(raw));
  return out;
}

bool writeLunaPng(const std::filesystem::path& file) {
  constexpr std::uint32_t width = 64;
  constexpr std::uint32_t height = 64;
  std::vector<std::uint8_t> raw;
  for (std::uint32_t y = 0; y < height; ++y) {
    raw.push_back(0);
    for (std::uint32_t x = 0; x < width; ++x) {
      const int dx = static_cast<int>(x) - 36;
      const int dy = static_cast<int>(y) - 28;
      const bool moon = dx * dx + dy * dy < 18 * 18 && (static_cast<int>(x) - 44) * (static_cast<int>(x) - 44) + (static_cast<int>(y) - 22) * (static_cast<int>(y) - 22) > 18 * 18;
      raw.push_back(moon ? 124 : 22);
      raw.push_back(moon ? 92 : 22);
      raw.push_back(moon ? 255 : 38);
      raw.push_back(255);
    }
  }
  std::vector<std::uint8_t> png{137, 80, 78, 71, 13, 10, 26, 10};
  std::vector<std::uint8_t> ihdr;
  appendU32(ihdr, width);
  appendU32(ihdr, height);
  ihdr.insert(ihdr.end(), {8, 6, 0, 0, 0});
  appendChunk(png, {'I', 'H', 'D', 'R'}, ihdr);
  appendChunk(png, {'I', 'D', 'A', 'T'}, zlibStore(raw));
  appendChunk(png, {'I', 'E', 'N', 'D'}, {});
  std::filesystem::create_directories(file.parent_path());
  std::ofstream out(file, std::ios::binary);
  out.write(reinterpret_cast<const char*>(png.data()), static_cast<std::streamsize>(png.size()));
  return static_cast<bool>(out);
}

bool writeWallpaper(const std::filesystem::path& file) {
  std::filesystem::create_directories(file.parent_path());
  std::ofstream out(file);
  out << "P3\n16 16\n255\n";
  for (int y = 0; y < 16; ++y) {
    for (int x = 0; x < 16; ++x) {
      out << 16 + x * 6 << ' ' << 16 + y * 3 << ' ' << 40 + x * 8 << '\n';
    }
  }
  return static_cast<bool>(out);
}
}

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cerr << "usage: luna-asset-generator output-directory\n";
    return 2;
  }
  const std::filesystem::path root = argv[1];
  const bool png = writeLunaPng(root / "png" / "luna.png");
  const bool wallpaper = writeWallpaper(root / "wallpapers" / "aurora.ppm");
  if (!png || !wallpaper) {
    std::cerr << "asset generation failed\n";
    return 1;
  }
  return 0;
}
