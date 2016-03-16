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

void LocalDataManager::writeRecentWinBallData(QList<DLT_WIN_BALL_DATA> *list)
{
    // start to write the recent win data to the local file
   QFile file(WINBALLFILE);
   if(file.open(QIODevice::WriteOnly | QIODevice::Text))
   {
       QString str = recentWinBalllsData2QString(list);
       qDebug() << "---> " << str;
        QTextStream out(&file);
        out << str;
       file.close();
       qDebug() << "write recent win balls data finished";
   }
   else
   {
        qDebug() << "write recent win balls data failed";
   }

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

QString LocalDataManager::recentWinBalllsData2QString(QList<DLT_WIN_BALL_DATA> *list)
{
    QString str = "";
    if(list && list ->size() > 0)
    {
        str.append("{\"data\":[");

        for(int i = 0; i < list->size(); i++)
        {
            QString expectStr = list->at(i).expect;
            QString dateStr = list->at(i).date;

            str.append("{");

            str.append("\"" + EXPECT + "\":" + "\"" + expectStr + "\",");
            str.append("\"" + OPENTIME + "\":" + "\"" + dateStr + "\",");
            str.append("\"" + OPENCODE + "\":\"");
            // append red balls data
            for(int m = 0; m < 5; m++)
            {
                int x = list->at(i).m_ball.m_red[m];
                str.append(QString::number(x, 10));

                if(m < 4)
                str.append(",");
            }
            str.append("+");
            // append blue balls data
            for(int n = 0; n < 2; n++)
            {
                int x = list->at(i).m_ball.m_blue[n];
                str.append(QString::number(x, 10));

                if(n < 1)
                str.append(",");
            }
            str.append("\"}");

            if(i < list->size()-1)
            str.append(",");
        }

        str.append("]}");
    }

    return str;
}
