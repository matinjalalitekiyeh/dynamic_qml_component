import QtQuick.Controls
import QtQuick

import "qml/constants"

ApplicationWindow {
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
    }/* right side rectangle to seperate half win */

}
