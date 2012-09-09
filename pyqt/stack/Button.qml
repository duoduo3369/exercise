// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1


Rectangle {
    id: container

    signal updateTextRequired

    property string label_text: "button"
    property string label_color: "lightblue"
    property string button_color: "#086efb"


    width: buttonLabel.width + 20; height: buttonLabel.height + 5
    color: button_color
    border { width: 1; color: "#100495" }
    smooth: true
    radius: 8
    function updateText(text){
        buttonLabel.text = text
    }

    Text {
        id: buttonLabel
        anchors.centerIn: container
        color: label_color
        text: label_text
        font.bold: true
        verticalAlignment: Text.AlignTop
        horizontalAlignment: Text.AlignLeft
        smooth: false
        styleColor: "#000000"
    }
    MouseArea{
        anchors.fill: parent
        onClicked: {
            container.focus = true;
            textInput.openSoftwareInputPanel()
            updateTextRequired()
        }
    }
    TextInput {
        id: textInput
        anchors.left: parent.left
        anchors.leftMargin: 8
        anchors.verticalCenter: parent.verticalCenter

        focus: true
        font.pixelSize:20
    }
}
