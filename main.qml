import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQml 2.2
import DLTManager 1.0

ApplicationWindow {
    id: root
    visible: true
    width: 480
    height: 640
    title: qsTr("Lottery")

    // the main view of the lotter
    Item {
        id : mainView
        anchors.fill: parent

        HistoryWinNumberView {
            anchors.fill: parent
        }
    }

    Connections {
        target: DLTManager
        onRecentWinBallsDataChanged : console.log("111");
    }
}

