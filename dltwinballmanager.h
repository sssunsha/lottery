#ifndef DLTWINBALLMANAGER_H
#define DLTWINBALLMANAGER_H

#include "constant.h"
#include "networkmanager.h"
#include "localdatamanager.h"
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
    void fetchRecentWinBallDataFromWeb();
    QList<DLT_WIN_BALL_DATA>* m_recent_win_balls;

    NetworkManager* getNetWorkManager();
    LocalDataManager* getLocalDataManager();

public slots:
    // for network manager
    void handleFetchRecentWinBallsDataFinished();
    void handleFetchRecentWinBallsDataError();

    // for localdatamanager
    void handleLoadRecentWinBallDataFinished();
    void handleLoadRecentWinBallDataFailed();
    void handleLoadSuggestBallDataFinished();
    void handleLoadSuggestBallDataFailed();

private:    
    NetworkManager* m_nwm;
    LocalDataManager* m_ldm;

};

#endif // DLTWINBALLMANAGER_H
