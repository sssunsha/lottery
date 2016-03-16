#include "localdatamanager.h"
#include "dltwinballmanager.h"
#include <QFile>
#include <QDir>

const QString WINBALLFILE = "/tmp/lottery/recentwinball";
const QString SUGGESTBALLFILE = "/tmp/lottery/suggestball";

const QString LOCALFOLDER = "/tmp/lottery/";

LocalDataManager::LocalDataManager(QObject *parent)
    :QObject(parent)
{
    connect(this, SIGNAL(loadRecentWinBallDataFinished()),
            this->parent(), SLOT(handleLoadRecentWinBallDataFinished()));
    connect(this, SIGNAL(loadRecentWinBallDataFailed()),
            this->parent(), SLOT(handleLoadRecentWinBallDataFailed()));
    connect(this, SIGNAL(loadSuggestBallDataFinished()),
            this->parent(), SLOT(handleLoadSuggestBallDataFinished()));
    connect(this, SIGNAL(loadSuggestBallDataFailed()),
            this->parent(), SLOT(handleLoadSuggestBallDataFailed()));

    init();
}

void LocalDataManager::loadRecentWinBallData()
{
    // start to do read the local recent win ball data
    QFile file(WINBALLFILE);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            qDebug() << line;
        }
        file.close();
        emit(loadRecentWinBallDataFinished());
    }
    else
    {
        emit(loadRecentWinBallDataFailed());
    }



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

void LocalDataManager::init()
{
    checkLocalFolderExist();
    checkLocalFileExist();
}

void LocalDataManager::checkLocalFolderExist()
{
       // check the /temp/lottery is exist or not, if not create
    QDir dir(LOCALFOLDER);
    if(!dir.exists())
    {
        qDebug() << "create the local folder to store data";
        dir.mkpath(LOCALFOLDER);
    }
}

void LocalDataManager::checkLocalFileExist()
{
    // check the file is exist or not,if not create it
    QFile win_file(WINBALLFILE);
    if(!win_file.exists())
    {
        qDebug() << "create the local recent win ball file";
        win_file.open(QIODevice::WriteOnly | QIODevice::Text);
    }

    QFile suggest_file(SUGGESTBALLFILE);
    if(!suggest_file.exists())
    {
        qDebug() << "create the local suggest win ball file";
        suggest_file.open(QIODevice::WriteOnly | QIODevice::Text);
    }
}
