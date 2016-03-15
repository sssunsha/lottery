#ifndef DLTWINBALLMANAGER_H
#define DLTWINBALLMANAGER_H

#include "constant.h"
#include "networkmanager.h"
#include <QString>
#include <QList>
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
    QList<DLT_WIN_BALL>* m_recent_win_balls;

public slots:
    void handleFetchRecentWinBallsDataFinished();
    void handleFetchRecentWinBallsDataError();
private:    
    NetworkManager* m_nwm;

};

#endif // DLTWINBALLMANAGER_H
