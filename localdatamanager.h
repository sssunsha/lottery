#ifndef LOCALDATAMANAGER_H
#define LOCALDATAMANAGER_H

#include <QObject>
#include "constant.h"

class LocalDataManager : public QObject
{
    Q_OBJECT
public:
    LocalDataManager(QObject* parent = 0);

    void loadRecentWinBallData();
    void loadSuggestBallData();
    void writeRecentWinBallData();
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
};

#endif // LOCALDATAMANAGER_H
