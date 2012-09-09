# coding=UTF8
import sys

from PyQt4.QtCore import QDateTime, QObject, QUrl, pyqtSignal,QTimer
from PyQt4.QtGui import QApplication
from PyQt4.QtDeclarative import QDeclarativeView
from PyQt4 import QtNetwork
from linked_list import *
# This class will emit the current date and time as a signal when
# requested.
class Stack(QObject):
    top_element = pyqtSignal(str)
    push_element = pyqtSignal(str)
    pop_element = pyqtSignal(str)
    
    def __init__(self):
        super(QObject,self).__init__()
        self.head = None
        self.tail = None
        
    def push(self, value):        
        if self.head is None:
            self.head = Node(value)
            self.tail = self.head
        else:
            self.tail.next = Node(value)
            self.tail = self.tail.next
        self.push_element.emit(str(value))

    def pop(self):
        if self.head is None:
            raise ListException      
        
        value = self.tail.value
        head = self.head
        if head.next is None:
            self.head = None
            return value
        while head.next is not self.tail:
            head = head.next
        self.tail = head
        self.tail.next = None
        self.pop_element.emit(str(value))
        return value
    
def main():

    app = QApplication(sys.argv)
    stack = Stack()
    # Create the QML user interface.
    view = QDeclarativeView()
    view.setSource(QUrl('stack.qml'))
    view.setResizeMode(QDeclarativeView.SizeRootObjectToView)
    view.setWindowTitle(u'栈')
    # Get the root object of the user interface.  It defines a
    # 'messageRequired' signal and JavaScript 'updateMessage' function.  Both
    # can be accessed transparently from Python.
    rootObject = view.rootObject()

    # Provide the current date and time when requested by the user interface.
    rootObject.button_clicked.connect(stack.push)

    # Update the user interface with the current date and time.
    stack.push_element.connect(rootObject.first_clicked)
    # Provide an initial message as a prompt.
    #rootObject.updateMessage(u"转眼间,你我已相遇...")
    
    stack.push(2)
    # Display the user interface and allow the user to interact with it.
    view.setGeometry(80, 80, 960, 580)
    view.show()

    app.exec_()

if __name__ == '__main__':
    main()
