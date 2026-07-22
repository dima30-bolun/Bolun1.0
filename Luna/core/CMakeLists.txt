add_library(luna_core STATIC EventBus.cpp Logger.cpp ConfigStore.cpp Theme.cpp ResourceIndex.cpp)
target_include_directories(luna_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_options(luna_core PRIVATE -Wall -Wextra -Wpedantic)
