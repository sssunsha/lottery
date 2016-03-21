#ifndef LOCALDATAMANAGER_H
#define LOCALDATAMANAGER_H

#include <QObject>
#include <QString>

#include "constant.h"

class LocalDataManager : public QObject
{
    Q_OBJECT
public:
    LocalDataManager(QObject* parent = 0);

    void loadRecentWinBallData();
    void loadSuggestBallData();
    void writeRecentWinBallData(QList<DLT_WIN_BALL_DATA>* list);
    void writeSuggestBallData();

signals:
    void loadRecentWinBallDataFinished();
    void loadRecentWinBallDataFailed();
    void loadSuggestBallDataFinished();
    void loadSuggestBallDataFailed();

private:
    void init();
    void checkLocalFolderExist();
    void checkLocalFileExist();
    QString recentWinBalllsData2QString(QList<DLT_WIN_BALL_DATA>* list);
    bool QString2RecentWinBallsData(QString data);
    DLT_WIN_BALL parseWinBalls(QString openCodeStr);

};

#endif // LOCALDATAMANAGER_H
