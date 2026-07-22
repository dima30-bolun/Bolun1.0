qt_add_executable(luna-shell main.cpp)
qt_add_qml_module(luna-shell URI LunaShell VERSION 1.0 QML_FILES qml/Main.qml qml/Tile.qml)
target_link_libraries(luna-shell PRIVATE Qt6::Core Qt6::Gui Qt6::Qml Qt6::Quick luna_core luna_services)
