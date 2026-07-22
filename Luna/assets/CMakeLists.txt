add_executable(luna-asset-generator AssetGenerator.cpp)
target_compile_options(luna-asset-generator PRIVATE -Wall -Wextra -Wpedantic)
set(LUNA_GENERATED_ASSET_DIR ${CMAKE_BINARY_DIR}/generated-assets)
add_custom_command(
  OUTPUT ${LUNA_GENERATED_ASSET_DIR}/png/luna.png ${LUNA_GENERATED_ASSET_DIR}/wallpapers/aurora.ppm
  COMMAND luna-asset-generator ${LUNA_GENERATED_ASSET_DIR}
  DEPENDS luna-asset-generator
  VERBATIM)
add_custom_target(luna-generated-assets ALL DEPENDS ${LUNA_GENERATED_ASSET_DIR}/png/luna.png ${LUNA_GENERATED_ASSET_DIR}/wallpapers/aurora.ppm)
