import QtQuick
import QtQuick.Controls
Window { id: root; width: 1280; height: 800; visible: true; color: "#10101a"; title: "Luna Shell"
  Rectangle { anchors.fill: parent; gradient: Gradient { GradientStop { position: 0; color: "#2b1d58" } GradientStop { position: 1; color: "#10101a" } } }
  GridView { id: grid; anchors.fill: parent; anchors.margins: 48; cellWidth: 180; cellHeight: 150; model: ["Explorer","Browser","Store","Terminal","Settings","Gallery","Camera","Music","Video","Notes","Calendar","Calculator","Task Manager","Packages","Update"] ; delegate: Tile { title: modelData; width: 160; height: 120 } }
  TextField { placeholderText: qsTr("Search applications"); anchors.horizontalCenter: parent.horizontalCenter; y: 24; width: 420 }
}
