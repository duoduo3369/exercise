import QtQuick 1.1
import QtDesktop 0.1
Rectangle {
    width: childrenRect.width
    height: childrenRect.height
    Row{
        Rectangle{
            color:"yellow"
            width:200
            height:200
        }
        Image{
            source:"images/logo_loading.gif"
        }
        TextArea {
            anchors.fill:parent
            id: area
            frame: frameCheckbox.checked
            text: "Hello world"
            KeyNavigation.tab: button1

        }
    }
}