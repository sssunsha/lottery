#include "dltwinballmanager.h"

#include <QDebug>
#include <QDate>
#include <QTime>
#include <QString>
#include <QStringList>

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
    // first load local recent win data
    loadLocalWinBallData();

    // second load suggest win data
    loadSuggestBallData();

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

// check if need to fetch new data online
bool DLTWINBallManager::needFetchNewWinBallsData()
{
    if(this->m_recent_win_balls && this->m_recent_win_balls->size() > 0)
    {
        // format for the target date and time

        QString str = this->m_recent_win_balls->at(0).date;

        QStringList strList = str.split(" ");
        QStringList strDateList = ((QString)strList.at(0)).split("-");
        QStringList strTimeList = ((QString)strList.at(1)).split(":");

        bool ok;
        int year = QString(strDateList.at(0)).toInt(&ok, 10);
        int month = QString(strDateList.at(1)).toInt(&ok, 10);
        int day = QString(strDateList.at(2)).toInt(&ok, 10);
        QDate strDate =  QDate(year, month, day);

        int hour = QString(strTimeList.at(0)).toInt(&ok, 10);
        int minute = QString(strTimeList.at(1)).toInt(&ok, 10);
        int second = QString(strTimeList.at(2)).toInt(&ok, 10);

        QTime strTime = QTime(hour, minute, second);


        // get the current date and time
        QDate date;
        date = date.currentDate();


        QTime time;
        time = time.currentTime();
        QTime time21 = QTime(21, 0, 0);

        // get the day of the current date
        if(date > strDate)
        {
            int dayofyear_date = date.dayOfYear();
            int dayofyear_strDate = strDate.dayOfYear();
            int dayofweek_strDate = strDate.dayOfWeek();

            if(dayofyear_date > dayofyear_strDate)
            {
                // same years
                switch (dayofyear_date - dayofyear_strDate) {
                case 1:
                    // no need to sync
                    return false;
                    break;
                case 2:
                    // if target day is 1 or 6 and currentTime is over 21 go to sync
                    if((dayofweek_strDate == 1 || dayofweek_strDate == 6) && time >= time21)
                    {
                        // go to sync
                        return true;
                    }
                    else
                    {
                        // no need to sync
                        return false;
                    }
                    break;
                case 3:
                    // if target day is 3 and currentTime is less than 21 no need to sync
                    if(dayofweek_strDate == 3 && time < time21)
                    {
                        // no need to sync
                        return false;
                    }
                    else
                    {
                        // go to sync
                        return true;
                    }
                    break;
                default:
                    // go to sync
                    return true;
                    break;
                }
            }
            else
            {
                // different years
                if(dayofyear_date > 2)
                {
                    // go to sync
                    return true;
                }
                else
                {
                    // no need to sync
                    return false;
                }
            }
        }

        return false;

    }
    else
    {
        return true;
    }
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

//
// fetch online recent win balls data slots
//

void DLTWINBallManager::handleFetchRecentWinBallsDataFinished(QList<DLT_WIN_BALL_DATA> *ball)
{
    setRecentWinBallsData(ball);

    // also write the data to local file
    m_ldm->writeRecentWinBallData(this->m_recent_win_balls);
    qDebug() << "fetch Recent Win ball finished";
}

void DLTWINBallManager::handleFetchRecentWinBallsDataError()
{
    qDebug() << "fetch Recent Win ball falied";
}

//
// load local recent win balls data slots
//

void DLTWINBallManager::handleLoadRecentWinBallDataFinished()
{
    qDebug() << "load recent win ball data finished";

    // check the timestamp for new round of data is generated now
    if(needFetchNewWinBallsData())
    {
        qDebug() << "need to sync for the new win balls data";
        fetchRecentWinBallDataFromWeb();
    }
    else
    {
        qDebug() << "no need to sync for the new win balls data";
    }
}

void DLTWINBallManager::handleLoadRecentWinBallDataFailed()
{
    qDebug() << "load recent win ball data failed";

    // falied to load the local data
    fetchRecentWinBallDataFromWeb();
}

//
// load local suggest win balls data slots
//

void DLTWINBallManager::handleLoadSuggestBallDataFinished()
{
    qDebug() << "load suggest ball data finished";
}

void DLTWINBallManager::handleLoadSuggestBallDataFailed()
{
    qDebug() << "load suggest ball data failed";
}

