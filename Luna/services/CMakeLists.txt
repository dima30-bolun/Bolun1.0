add_library(luna_services STATIC ApplicationCatalog.cpp SearchEngine.cpp NotificationCenter.cpp WallpaperEngine.cpp)
target_include_directories(luna_services PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(luna_services PUBLIC luna_core luna_formats)
target_compile_options(luna_services PRIVATE -Wall -Wextra -Wpedantic)
