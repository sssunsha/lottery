import QtQuick 2.5
import DLTManager 1.0

//Column {
//    Repeater {
//        model : DLTManager.getRecentWinBallsDataCount();
//        Text {
//            text: DLTManager.getRecentWinBallsData4ExceptAt(index) + " ------- "
//                  + DLTManager.getRecentWinBallsData4RedBallsAt(index) + "  ||  "
//                  + DLTManager.getRecentWinBallsData4BlueBallsAt(index)
//        }
//    }
//}

Rectangle{
    id: root
    color: "white"
    property int winball_round: DLTManager.getRecentWinBallsDataCount();
    Grid {
      id: winball_grid
      anchors.fill: parent
      spacing: 3
      columns : 47
      property real ball_width: (parent.width - 46 * winball_grid.spacing) / 47
      property real ball_height:(parent.height - root.winball_round * winball_grid.spacing) / (root.winball_round + 1)
      property int ball_count: 47 * root.winball_round
      property int m: root.winball_round - 1
      Repeater {
          model : 47
          Rectangle {
              color: (index >34 ) ? "#436EEE" : "#FF8247"
              width:winball_grid.ball_width
              height: winball_grid.ball_height
              Text {
                  anchors.centerIn: parent
                  text: (index > 34) ? (index -34) : (index + 1)
                  font.bold: true
              }
          }
      }
      Repeater {
          model : winball_grid.ball_count
          Rectangle {
              id : winball_panel
              property int i: index%47 >34
              color: (winball_panel.i) ? "#436EEE" : "#FF8247"
              width:winball_grid.ball_width
              height: winball_grid.ball_height
              Text {
                  anchors.centerIn: parent
                  font.bold: true
                  text : (winball_panel.i) ?
                             DLTManager.getRecentWinBallsData4BlueBalsAt( (winball_grid.m - index/47), index%47 -35) :
                             DLTManager.getRecentWinBallsData4RedBallAt( (winball_grid.m - index/47), index%47)
                  color: (winball_panel.i ) ? "#262626" : "#A52A2A"
                  font.pixelSize: 20
              }
          }
      }
    }
}
