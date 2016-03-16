#ifndef DLTWINBALLMANAGER_H
#define DLTWINBALLMANAGER_H

#include "constant.h"
#include "networkmanager.h"
#include "localdatamanager.h"
#include <QString>
#include <QList>
// DLT win ball manager

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
    bool needFetchNewWinBallsData();

    void setRecentWinBallsData(QList<DLT_WIN_BALL_DATA>* list);
    QList<DLT_WIN_BALL_DATA> *getRecentWinBallsData();

    NetworkManager* getNetWorkManager();
    LocalDataManager* getLocalDataManager();

public slots:
    // for network manager
    void handleFetchRecentWinBallsDataFinished(QList<DLT_WIN_BALL_DATA>* ball);
    void handleFetchRecentWinBallsDataError();

    // for localdatamanager
    void handleLoadRecentWinBallDataFinished();
    void handleLoadRecentWinBallDataFailed();
    void handleLoadSuggestBallDataFinished();
    void handleLoadSuggestBallDataFailed();

private:    
    QList<DLT_WIN_BALL_DATA>* m_recent_win_balls;
    NetworkManager* m_nwm;
    LocalDataManager* m_ldm;

};

#endif // DLTWINBALLMANAGER_H
