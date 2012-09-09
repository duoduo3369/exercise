// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {
    signal button_clicked;
    id: container
    width:250
    height: 540
    property int count: 10
    Button{
        id:stack
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 5
        button_width: 60
        button_height: 400
    }
    function last_clicked(parent,pre){
        if(parent.pushable){

            parent.state = 'in_stack_bottom'
            parent.pushable = false
            parent.popable = true
            pre.popable = false

        }
        else if(parent.popable){
            parent.state = "out_stack_bottom"
            parent.pushable = true
            parent.popable = false
            pre.popable = true

        }
    }
    function middle_clicked(parent,pre,next){
        if(parent.pushable){

            parent.state = 'in_stack_bottom'
            parent.pushable = false
            parent.popable = true

            pre.popable = false
            next.pushable = true
        }
        else if(parent.popable){
            parent.state = "out_stack_bottom"
            parent.pushable = true
            parent.popable = false

            next.pushable = false
            pre.popable = true

        }

    }
    function first_clicked(parent,next){
        if(parent.pushable){

            parent.state = 'in_stack_bottom'
            parent.pushable = false
            parent.popable = true
            next.pushable = true
        }
        else if(parent.popable){
            parent.state = "out_stack_bottom"
            parent.pushable = true
            parent.popable = false
            next.pushable = false
        }
    }

    Button{
        id: b_3
        color: "#32f90a"
        z: b_2.z - 1
        label_text: "3"
        button_width:stack.button_width
        button_height:stack.button_height / container.count
        state: "out_stack_bottom"
        pushable: false
        popable: false
        MouseArea{

            anchors.fill: parent
            onClicked: {
                container.last_clicked(parent,b_2)
            }
        }
        states: [
            State{
                name: "out_stack_bottom"
                PropertyChanges {
                    target: b_3;
                    anchors.left: stack.right
                    anchors.leftMargin: 70
                    anchors.bottom: stack.bottom
                    anchors.bottomMargin: 0
                }

            },
            State{
                name: "in_stack_bottom"
                PropertyChanges {
                    target: b_3
                    anchors.left: stack.left
                    anchors.leftMargin: 0
                    anchors.bottom: b_2.top
                }
            }

        ]
        transitions: [
            Transition {
                from: "out_stack_bottom"
                to: "in_stack_bottom"
                SequentialAnimation{

                    NumberAnimation {
                        duration: 250;
                        property: "anchors.bottomMargin"
                        to: 450
                    }

                    NumberAnimation { duration: 250;
                        property: "anchors.leftMargin"
                        to:-b_1.button_width
                    }
                    NumberAnimation {
                        duration: 250;
                        property: "anchors.bottomMargin"
                        to:0
                    }

                }
            },
            Transition {
                from: "in_stack_bottom"
                to: "out_stack_bottom"
                SequentialAnimation{
                    NumberAnimation {
                        duration: 250;
                        property: "anchors.bottomMargin"
                        to: stack.height + 50

                    }

                    NumberAnimation { duration: 250;
                        property: "anchors.leftMargin"
                        to:70 + b_1.button_width
                    }
                    NumberAnimation {
                        duration: 250;
                        property: "anchors.bottomMargin"
                        to:0
                    }
                }
            }
        ]

    }

    Button{
        id: b_2
        z: b_1.z - 1
        color: "#ffe203"
        label_text: "2"
        button_width:stack.button_width
        button_height:stack.button_height / container.count

        state: "out_stack_bottom"
        pushable: false
        popable: false
        MouseArea{
            anchors.fill: parent
            onClicked: {
                container.middle_clicked(parent,b_1,b_3)
            }
        }
        states: [
            State{
                name: "out_stack_bottom"
                PropertyChanges {
                    target: b_2;
                    anchors.left: stack.right
                    anchors.leftMargin: 70
                    anchors.bottom: stack.bottom
                    anchors.bottomMargin: 0
                }

            },
            State{
                name: "in_stack_bottom"
                PropertyChanges {
                    target: b_2
                    anchors.left: stack.left
                    anchors.leftMargin: 0
                    anchors.bottom: b_1.top
                }
            }

        ]
        transitions: [
            Transition {
                from: "out_stack_bottom"
                to: "in_stack_bottom"
                SequentialAnimation{

                    NumberAnimation {
                        duration: 250;
                        property: "anchors.bottomMargin"
                        to:stack.height + 50

                    }

                    NumberAnimation { duration: 250;
                        property: "anchors.leftMargin"
                        to:-b_1.button_width
                    }
                    NumberAnimation {
                        duration: 250;
                        property: "anchors.bottomMargin"
                        to:0
                    }

                }
            },
            Transition {
                from: "in_stack_bottom"
                to: "out_stack_bottom"
                SequentialAnimation{
                    NumberAnimation {
                        duration: 250;
                        property: "anchors.bottomMargin"
                        to:stack.height + 50
                    }

                    NumberAnimation { duration: 250;
                        property: "anchors.leftMargin"
                        to:70 + b_1.button_width
                    }
                    NumberAnimation {
                        duration: 250;
                        property: "anchors.bottomMargin"
                        to:0
                    }
                }
            }
        ]



    }

    Button{
        id: b_1
        z: parent.count
        color: "#fb0808"
        label_text: "1"
        button_width:stack.button_width
        button_height:stack.button_height / container.count

        state: "out_stack_bottom"
        pushable: true
        popable: false
        MouseArea{
            anchors.fill: parent
            onClicked: {
                container.first_clicked(parent,b_2)
            }
        }
        states: [
            State{
                name: "out_stack_bottom"
                PropertyChanges {
                    target: b_1;
                    anchors.left: stack.right
                    anchors.leftMargin: 70
                    anchors.bottom: stack.bottom
                    anchors.bottomMargin: 0
                }

            },
            State{
                name: "in_stack_bottom"
                PropertyChanges {
                    target: b_1
                    anchors.left: stack.left
                    anchors.leftMargin: 0
                }
            }

        ]
        transitions: [
            Transition {
                from: "out_stack_bottom"
                to: "in_stack_bottom"
                SequentialAnimation{

                    NumberAnimation {
                        duration: 250;
                        property: "anchors.bottomMargin"
                        to:stack.height + 50

                    }

                    NumberAnimation { duration: 250;
                        property: "anchors.leftMargin"
                        to:-b_1.button_width
                    }
                    NumberAnimation {
                        duration: 250;
                        property: "anchors.bottomMargin"
                        to:0
                    }

                }
            },
            Transition {
                from: "in_stack_bottom"
                to: "out_stack_bottom"
                SequentialAnimation{
                    NumberAnimation {
                        duration: 250;
                        property: "anchors.bottomMargin"
                        to: stack.height + 50

                    }

                    NumberAnimation { duration: 250;
                        property: "anchors.leftMargin"
                        to:70 + b_1.button_width
                    }
                    NumberAnimation {
                        duration: 250;
                        property: "anchors.bottomMargin"
                        to:0
                    }
                }
            }
        ]

    }

}
