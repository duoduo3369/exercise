# coding=UTF8
import sys

from PyQt4.QtCore import QDateTime, QObject, QUrl, pyqtSignal,QTimer
from PyQt4.QtGui import QApplication
from PyQt4.QtDeclarative import QDeclarativeView
from PyQt4 import QtNetwork
# This class will emit the current date and time as a signal when
# requested.
class SignalTest(QObject):
    signal_test = pyqtSignal(str)
        
    def change_text(self,text):
        self.singal_text.emit(text)
    
def main():

    app = QApplication(sys.argv)
    test = SignalTest()
    # Create the QML user interface.
    view = QDeclarativeView()
    view.setSource(QUrl('Button.qml'))
    view.setResizeMode(QDeclarativeView.SizeRootObjectToView)
    view.setWindowTitle(u'栈')
    rootObject = view.rootObject()

    rootObject.updateTextRequired.connect(test.change_text)

    # Update the user interface with the current date and time.
    test.signal_test.connect(rootObject.updateText)
    # Provide an initial message as a prompt.
    rootObject.updateText(u"转眼间,你我已相遇...")
    
    #stack.push(2)
    # Display the user interface and allow the user to interact with it.
    view.setGeometry(80, 80, 960, 580)
    view.show()

    app.exec_()

if __name__ == '__main__':
    main()
