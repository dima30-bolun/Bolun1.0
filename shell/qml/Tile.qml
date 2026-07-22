import QtQuick
import QtQuick.Controls
Rectangle { id: tile; property string title: ""; radius: 22; color: "#aa7c5cff"; border.color: "#66ffffff"; scale: mouse.pressed ? 0.96 : 1.0
  Behavior on scale { NumberAnimation { duration: 120; easing.type: Easing.OutCubic } }
  layer.enabled: true; layer.samples: 4
  Text { anchors.centerIn: parent; text: title; color: "white"; font.pixelSize: 18 }
  MouseArea { id: mouse; anchors.fill: parent; drag.target: tile }
}
