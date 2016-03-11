#ifndef DLTWINBALLMANAGER_H
#define DLTWINBALLMANAGER_H

#include "constant.h"
#include "networkmanager.h"
#include <QString>
// DLT win ball manager

const QString WINBALLFILEPATH = "./winball";
const QString SUGGESTBALLFILEPATH = "./sugge";



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
};

#endif // DLTWINBALLMANAGER_H
