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

          Repeater {
                    model: m_model;
                    delegate:
                        DQC_Rectangle {
                                  // color: "cyan";
                                  x: initial_x;
                                  y: initial_y;
                                  text: is_at_left_zone ? data_source+" "+random_num : "XXXXXX";
                                  color: _color;
                                  interval: interval;
                                  onRandom_numChanged: is_at_left_zone ? data_source+" "+random_num : "XXXXXX";
                        }
          }

}
