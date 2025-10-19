import QtQuick
import QtQuick.Controls

Rectangle {
    id:             rect;
    width:          150;
    height:         75;
    radius:         8;
    border.color:   "#88888888";

    function get_random_int(min, max) {
        return Math.floor(Math.random() * (max - min + 1)) + min;
    }

    // function generate_random() {
    //     return getRandomInt(-10, 20);
    // }

    property bool is_at_left_zone: (((rect.width) + rect.x) < mainwindow.width/2);
    property string text: "";
    property int random_min: 0;
    property int random_max: 100;
    property int random_num: 0;
    property int interval: 1000;

    Label {
        text: rect.text;
        anchors.centerIn: parent;
        color: "black";
    }

    SequentialAnimation on x {
        loops: Animation.Infinite;
        running: true;

        PropertyAnimation {
            to: (mainwindow.width - rect.width);
            duration: Math.abs((mainwindow.width - rect.width - rect.x) / speed);
        }

        PropertyAnimation {
            to: 0;
            duration: Math.abs((0 - (mainwindow.width - rect.width)) / speed);
        }
    }
    Timer {
        interval: rect.interval;
        repeat: rect.is_at_left_zone;
        running: rect.is_at_left_zone;
        onTriggered: rect.random_num = rect.get_random_int(rect.random_min, rect.random_max);
    }
}
