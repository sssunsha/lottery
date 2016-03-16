#include "dltwinballmanager.h"

DLTWINBallManager::DLTWINBallManager(QObject* parent)
    :QObject(parent)
{
    this->m_recent_win_balls = NULL;
    this->m_nwm = new NetworkManager(this);
    this->m_ldm = new LocalDataManager(this);
}

// init
bool DLTWINBallManager::init()
{
    loadLocalWinBallData();
    loadSuggestBallData();
    fetchRecentWinBallDataFromWeb();
    return true;
}

void DLTWINBallManager::loadLocalWinBallData()
{
    this->m_ldm->loadRecentWinBallData();
}

void DLTWINBallManager::loadSuggestBallData()
{
    this->m_ldm->loadSuggestBallData();
}

void DLTWINBallManager::fetchRecentWinBallDataFromWeb()
{
    // start to fectch the recent win ball from web
    this->m_nwm->load_recent_balls();
}

void DLTWINBallManager::setRecentWinBallsData(QList<DLT_WIN_BALL_DATA> *list)
{
    if(list && list->size() > 0)
    {
        if(this->m_recent_win_balls)
        {
            delete this->m_recent_win_balls;
        }
        this->m_recent_win_balls = list;
    }
    else
    {
        delete list;
        list = NULL;
    }
}

QList<DLT_WIN_BALL_DATA> *DLTWINBallManager::getRecentWinBallsData()
{
    return this->m_recent_win_balls;
}

NetworkManager *DLTWINBallManager::getNetWorkManager()
{
        return this->m_nwm;
}

LocalDataManager *DLTWINBallManager::getLocalDataManager()
{
    return this->m_ldm;
}

void DLTWINBallManager::handleFetchRecentWinBallsDataFinished(QList<DLT_WIN_BALL_DATA> *ball)
{
    setRecentWinBallsData(ball);
    qDebug() << "fetch Recent Win ball finished";
}

void DLTWINBallManager::handleFetchRecentWinBallsDataError()
{
    qDebug() << "fetch Recent Win ball falied";
}

void DLTWINBallManager::handleLoadRecentWinBallDataFinished()
{
    qDebug() << "load recent win ball data finished";
}

void DLTWINBallManager::handleLoadRecentWinBallDataFailed()
{
    qDebug() << "load recent win ball data failed";
}

void DLTWINBallManager::handleLoadSuggestBallDataFinished()
{
    qDebug() << "load suggest ball data finished";
}

void DLTWINBallManager::handleLoadSuggestBallDataFailed()
{
    qDebug() << "load suggest ball data failed";
}

