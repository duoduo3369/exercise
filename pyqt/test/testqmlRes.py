import os
import sys


from PyQt4.QtGui import *
from PyQt4.QtDeclarative import *
from PyQt4.QtCore import *
from PyQt4.QtNetwork import *

import test_qml_res

class MainWidget(QDeclarativeView):
    def __init__(self, parent=None, _platform=None):
        super(MainWidget,self).__init__(parent)
        self.setSource(QUrl("qrc:/qml/TestRect.qml"))
        self.setResizeMode(QDeclarativeView.SizeRootObjectToView)

if __name__ == '__main__':
    app = QApplication(sys.argv)
    dlg = MainWidget()
    dlg.show()
    app.exec_()
    
