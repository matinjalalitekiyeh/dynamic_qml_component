import QtQuick.Controls
import QtQuick

import "qml/constants"

ApplicationWindow {id: main;
    title:  Constants.project_name;
    width:  Constants.width;
    height: Constants.height;
    color:  Constants.background_color;
    visible: true;
    x: width/2;
    y: height/2;

    Rectangle {
        anchors.right: parent.right;
        width: parent.width/2;
        height: parent.height;
        color: "#99555555";
        z: 99;
    }/* right side rectangle to seperate half win */

    property real baseDuration: 10000 // Base duration for full width
      property real speed: (main.width - 250) / baseDuration // pixels per millisecond

      Rectangle {
          id: xxx
          width: 250
          height: 200
          color: "red"
          radius: 8
          y: 50

          onXChanged: {
              if (((xxx.width) + xxx.x) > main.width/2) {
                  xxx_txt.text = "Right";
              }else{
                  xxx_txt.text = "Left";
              }
          }

          Label {id: xxx_txt;
              text: "Left"
              anchors.centerIn: parent
              color: "black"
          }

          Component.onCompleted: {
              xxx.x = 380
          }

          SequentialAnimation on x {
              loops: Animation.Infinite
              running: true

              PropertyAnimation {
                  to: main.width - xxx.width
                  duration: Math.abs((main.width - xxx.width - xxx.x) / speed)
              }

              PropertyAnimation {
                  to: 0
                  duration: Math.abs((0 - (main.width - xxx.width)) / speed)
              }
          }
      }

      Rectangle {
          id: xxx2
          width: 250
          height: 200
          color: "green"
          radius: 8
          y: 400

          onXChanged: {
              if (((xxx2.width) + xxx2.x) > main.width/2) {
                  xxx2_txt.text = "Right";
              }else{
                  xxx2_txt.text = "Left";
              }
          }

          Label {id: xxx2_txt
              text: "Left"
              anchors.centerIn: parent
              color: "black"
          }

          Component.onCompleted: {
              xxx2.x = 200
          }

          SequentialAnimation on x {
              loops: Animation.Infinite
              running: true

              PropertyAnimation {
                  to: main.width - xxx2.width
                  duration: Math.abs((main.width - xxx2.width - xxx2.x) / speed)
              }

              PropertyAnimation {
                  to: 0
                  duration: Math.abs((0 - (main.width - xxx2.width)) / speed)
              }
          }
      }

}
