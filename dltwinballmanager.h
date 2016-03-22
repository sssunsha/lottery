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
    Q_DISABLE_COPY(DLTWINBallManager)
    Q_PROPERTY(QString appName READ appName WRITE setAppName)


public:
    explicit DLTWINBallManager(QObject* parent = 0);
    bool init();
    void loadLocalWinBallData();
    void loadSuggestBallData();
    void fetchRecentWinBallDataFromWeb();
    bool needFetchNewWinBallsData();

    void setRecentWinBallsData(QList<DLT_WIN_BALL_DATA>* list);
    Q_INVOKABLE QList<DLT_WIN_BALL_DATA> *getRecentWinBallsData();

    Q_INVOKABLE QString getRecentWinBallsData4ExceptAt(int index);
    Q_INVOKABLE QString getRecentWinBallsData4DateAt(int index);
    Q_INVOKABLE QString getRecentWinBallsData4RedBallsAt(int index);
    Q_INVOKABLE QString getRecentWinBallsData4BlueBallsAt(int index);
    Q_INVOKABLE int getRecentWinBallsDataCount();

    NetworkManager* getNetWorkManager();
    LocalDataManager* getLocalDataManager();

    QString appName();
    void setAppName(QString n);

signals:
    void recentWinBallsDataChanged();

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
    QString m_appName;
};

#endif // DLTWINBALLMANAGER_H
