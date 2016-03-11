#ifndef DLTWINBALLMANAGER_H
#define DLTWINBALLMANAGER_H

#include "constant.h"
#include "networkmanager.h"
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
    void check4FetchWinBallDataFromWeb();


private:
    NetworkManager* m_nwm;

};

#endif // DLTWINBALLMANAGER_H
