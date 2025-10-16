import QtQuick.Controls
import QtQuick

import "qml/constants"
import "qml/contents"

ApplicationWindow {
          id:       mainwindow;
          title:    Constants.project_name;
          width:    Constants.width;
          height:   Constants.height;
          color:    Constants.background_color;

          visibility: "Maximized";
          visible:  true;

          /* ! qmlproperty: Base duration for full width */
          property real baseDuration: 10000;
          /* ! qmlproperty: pixels per millisecond */
          property real speed: (mainwindow.width - 250) / baseDuration;

          Rectangle {
                    anchors.right: parent.right;
                    width: parent.width/2;
                    height: parent.height;
                    color: "#99555555";
                    z: 99;
          }/* right side rectangle to seperate half win */

          property real baseDuration: 10000 // Base duration for full width
          property real speed: (mainwindow.width - 250) / baseDuration // pixels per millisecond

          DQC_Rectangle {
                    color: "cyan";
                    x: 100;
                    y: 300;
                    onIs_left_zone: console.log("is at left zone: " + is_at_left_zone + " " + color);
          }

          DQC_Rectangle {
                    color: "red";
                    x: 200;
                    y: 450;
                    onIs_left_zone: console.log("is at left zone: " + is_at_left_zone + " " + color);
          }
}
