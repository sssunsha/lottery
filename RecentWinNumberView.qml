import QtQuick 2.5
import DLTManager 1.0

//ListView {
//    id : recent_win_number_view
//    anchors.fill: parent
//    model: test_model

//    delegate: Rectangle {
//         height: 25
//         width: 100
//         color: model.modelData.color
//         Text { text: name }
//     }
//}

Column {
    Repeater {
        model : DLTManager.getRecentWinBallsDataCount();
        Text {
            text: DLTManager.getRecentWinBallsData4ExceptAt(index) + " ------- "
                  + DLTManager.getRecentWinBallsData4RedBallsAt(index) + "  ||  "
                  + DLTManager.getRecentWinBallsData4BlueBallsAt(index)
        }
    }
}

