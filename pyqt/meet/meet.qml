import Qt 4.7

Rectangle {
    signal messageRequired;
    width: 1024
    height: 640

    function updateMessage(text) {
        messageText.text = text
    }

    anchors.fill: parent;
    color: "#40ee0f"
    border.color: "black"

    MouseArea{
        anchors.fill: parent
        onClicked: Qt.quit()
    }

    Image {
        id: image1
        x: -411
        y: -93
        width: 1024
        height: 640
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        opacity: 1
        source: "heart_2.jpg"

        Text {
            id: messageText;
            color: "white";
            text: qsTr("")
            font.family: "华文琥珀"
            font.pointSize: 16
            style: Text.Sunken
            anchors.top: parent.top
            anchors.topMargin: 80
            anchors.left: parent.left
            anchors.leftMargin: 80
            verticalAlignment: Text.AlignVCenter
            wrapMode: Text.WordWrap
            font.bold: true;
            smooth: true;
        clip :true;
    }
    }
}
