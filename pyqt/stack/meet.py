# coding=UTF8
import sys

from PyQt4.QtCore import QDateTime, QObject, QUrl, pyqtSignal,QTimer
from PyQt4.QtGui import QApplication
from PyQt4.QtDeclarative import QDeclarativeView
from PyQt4 import QtNetwork

# This class will emit the current date and time as a signal when
# requested.
class Now(QObject):

    now = pyqtSignal(str)
    meet = QDateTime(2012,6,2,8,0,0)

    def emit_now(self):
        formatted_date = self.meet.daysTo(QDateTime.currentDateTime())
        one_day_seconds = (self.meet.secsTo(QDateTime.currentDateTime())
                  - formatted_date *24 * 60 * 60)
        hours = one_day_seconds / 3600
        minutes = one_day_seconds / 60 - hours * 60 
        seconds = one_day_seconds % 60
        msgString = u'亲爱的,从我们相遇至今已经有 %s天 %s小时 %s分钟 %s秒了 \n\n\n你是我的天使,每一分钟,每一秒钟我都很宝贝.\n\n你呢 每天都要快快乐乐的知道么\n\n睡个好觉 做个好梦\n\n么么 wanan' \
                    % (unicode(formatted_date),unicode(hours),unicode(minutes),unicode(seconds),)
        self.now.emit(msgString)


def main():

    app = QApplication(sys.argv)

    now = Now()

    # Create the QML user interface.
    view = QDeclarativeView()
    view.setSource(QUrl('meet.qml'))
    view.setResizeMode(QDeclarativeView.SizeRootObjectToView)
    view.setWindowTitle(u'属于你我的时间')
    # Get the root object of the user interface.  It defines a
    # 'messageRequired' signal and JavaScript 'updateMessage' function.  Both
    # can be accessed transparently from Python.
    rootObject = view.rootObject()

    # Provide the current date and time when requested by the user interface.
    rootObject.messageRequired.connect(now.emit_now)

    # Update the user interface with the current date and time.
    now.now.connect(rootObject.updateMessage)
    timer = QTimer()
    timer.timeout.connect(now.emit_now)
    timer.start(500)
    # Provide an initial message as a prompt.
    rootObject.updateMessage(u"转眼间,你我已相遇...")

    # Display the user interface and allow the user to interact with it.
    view.setGeometry(80, 80, 960, 580)
    view.show()

    app.exec_()

if __name__ == '__main__':
    main()
