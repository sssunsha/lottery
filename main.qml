import QtQuick 2.3
import QtQuick.Controls 1.2

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
}

