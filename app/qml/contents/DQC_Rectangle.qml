import QtQuick
import QtQuick.Controls

Rectangle {
    id:             rect;
    width:          150;
    height:         75;
    radius:         8;
    border.color:   "#88888888";

    signal is_left_zone(bool is_at_left_zone);

    onXChanged: {
        if (((rect.width) + rect.x) > mainwindow.width/2) {
            rect_txt.text = "Right";
            is_left_zone(false);
        }else{
            is_left_zone(true);
            rect_txt.text = "Left";
        }
    }

    Label {
        id: rect_txt;
        text: "Left";
        anchors.centerIn: parent;
        color: "black";
    }

    SequentialAnimation on x {
        loops: Animation.Infinite;
        running: true;

        PropertyAnimation {
            to: mainwindow.width - rect.width;
            duration: Math.abs((mainwindow.width - rect.width - rect.x) / speed);
        }

        PropertyAnimation {
            to: 0;
            duration: Math.abs((0 - (mainwindow.width - rect.width)) / speed);
        }
    }
}
