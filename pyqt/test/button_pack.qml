// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {
    id: container
    width: 100
    height: 62

    ListModel {
        id: buttonModel
        ListElement { b_label_text: "1"; b_label_color: "black";b_button_color:"blue" }
        ListElement { b_label_text: "2"; b_label_color: "black";b_button_color:"blue" }
        ListElement { b_label_text: "3"; b_label_color: "black";b_button_color:"blue" }
        ListElement { b_label_text: "4"; b_label_color: "black";b_button_color:"blue" }
        ListElement { b_label_text: "5"; b_label_color: "black";b_button_color:"blue" }
        ListElement { b_label_text: "6"; b_label_color: "black";b_button_color:"blue" }
        ListElement { b_label_text: "7"; b_label_color: "black";b_button_color:"blue" }
        ListElement { b_label_text: "8"; b_label_color: "black";b_button_color:"blue" }

    }

    Component {
        id: buttonDelegate

            Button {
                //anchors.horizontalCenter: parent.horizontalCenter
                //anchors.verticalCenter: parent.verticalCenter

                label_text: b_label_text;
                label_color: b_label_color
                button_color:b_button_color

            }


    }

    ListView {
        id: buttonView
        width: 100
        height: 62
        highlightMoveSpeed: 400
        highlightRangeMode: ListView.ApplyRange
        boundsBehavior: Flickable.DragAndOvershootBounds
        flickableDirection: Flickable.VerticalFlick
        contentWidth: 0
        spacing: 2
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        model: buttonModel
        delegate: buttonDelegate


    }





}
