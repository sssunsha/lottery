#include "localdatamanager.h"
#include "dltwinballmanager.h"

LocalDataManager::LocalDataManager(QObject *parent)
    :QObject(parent)
{
    connect(this, SIGNAL(loadRecentWinBallDataFinished()),
            parent, SLOT(handleLoadRecentWinBallDataFinished()));
    connect(this, SIGNAL(loadRecentWinBallDataFailed()),
            parent, SLOT(handleLoadRecentWinBallDataFailed));
    connect(this, SIGNAL(loadSuggestBallDataFinished()),
            parent, SLOT(handleLoadSuggestBallDataFinished()));
    connect(this, SIGNAL(loadSuggestBallDataFailed()),
            parent, SLOT(handleLoadSuggestBallDataFailed()));
}

void LocalDataManager::loadRecentWinBallData()
{

}

void LocalDataManager::loadSuggestBallData()
{

}

void LocalDataManager::writeRecentWinBallData()
{

}

void LocalDataManager::writeSuggestBallData()
{

}
