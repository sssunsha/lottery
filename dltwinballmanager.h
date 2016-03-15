#ifndef DLTWINBALLMANAGER_H
#define DLTWINBALLMANAGER_H

#include "constant.h"
#include "networkmanager.h"
#include <QString>
// DLT win ball manager

const QString WINBALLFILE = "./winball50";
const QString SUGGESTBALLFILE = "./suggestball";

#include <QObject>

class DLTWINBallManager : public QObject
{
    Q_OBJECT
public:
    DLTWINBallManager(QObject* parent = 0);
    bool init();
    void loadLocalWinBallData();
    void loadSuggestBallData();
    bool check4FetchWinBallDataFromWeb();

private:
    NetworkManager* m_nwm;
    DLT_WIN_BALL m_recent_win_balls[RECENT_NUMBER];
};

#endif // DLTWINBALLMANAGER_H
