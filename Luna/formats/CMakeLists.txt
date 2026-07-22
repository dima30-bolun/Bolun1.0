add_library(luna_formats STATIC BenFormat.cpp BappPackage.cpp LunaProject.cpp)
target_include_directories(luna_formats PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(luna_formats PUBLIC luna_core)
target_compile_options(luna_formats PRIVATE -Wall -Wextra -Wpedantic)
