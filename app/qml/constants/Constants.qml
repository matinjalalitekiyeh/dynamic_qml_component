pragma Singleton

import QtQml
import QtQuick
import QtQuick.Window

QtObject {
    //! qmlproperty: qml project's name.
    readonly property string project_name: "Dynamic Qml Component";

    //! qmlproperty: screen width/hieght.
    readonly property double width: Screen.width;
    readonly property double height: Screen.height;

    //! qmlproperty: color in appwin.
    readonly property color background_color: "white";
}
