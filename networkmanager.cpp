#include "networkmanager.h"
#include "dltwinballmanager.h"
#include <QLoggingCategory>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

NetworkManager::NetworkManager(QObject* parent)
    :QObject(parent)
{
    // init QNetworkAccessManager
    m_net_access_manager = new QNetworkAccessManager(this);
    QLoggingCategory::setFilterRules("qt.network.ssl.warning=false");

    QObject::connect(m_net_access_manager, SIGNAL(finished(QNetworkReply*)),
                     this, SLOT(handleNetworkReply(QNetworkReply*)));

    QObject::connect(m_net_access_manager, SIGNAL(authenticationRequired(QNetworkReply*, QAuthenticator* )),
                     this, SLOT(hadleAuthenticationRequired(QNetworkReply*, QAuthenticator*)));

    QObject::connect(m_net_access_manager, SIGNAL(encrypted(QNetworkReply*)),
                     this, SLOT(handleEncrypted(QNetworkReply*)));

    QObject::connect(m_net_access_manager, SIGNAL(networkAccessibleChanged(QNetworkAccessManager::NetworkAccessibility)),
                     this, SLOT(handleNetworkAccessibleChanged(QNetworkAccessManager::NetworkAccessibility)));

    QObject::connect(m_net_access_manager, SIGNAL(preSharedKeyAuthenticationRequired(QNetworkReply*, QSslPreSharedKeyAuthenticator*)),
                     this, SLOT(handlePreSharedKeyAuthenticationRequired(QNetworkReply*, QSslPreSharedKeyAuthenticator*)));

    QObject::connect(m_net_access_manager, SIGNAL(proxyAuthenticationRequired(const QNetworkProxy&, QAuthenticator*)),
                     this, SLOT(handleProxyAuthenticationRequired(const QNetworkProxy&, QAuthenticator*)));

    QObject::connect(m_net_access_manager, SIGNAL(sslErrors(QNetworkReply*, const QList<QSslError>&)),
                     this, SLOT(handleSSLErrors(QNetworkReply*, const QList<QSslError>&)));

    // init other signal and slots
    connect(this, SIGNAL(fetchRecentWinBallsDataFinished(QList<DLT_WIN_BALL_DATA>*)),
            this->parent(), SLOT(handleFetchRecentWinBallsDataFinished(QList<DLT_WIN_BALL_DATA>*)));
    connect(this, SIGNAL(fetchRecentWinBallsDataError()),
            this->parent(), SLOT(handleFetchRecentWinBallsDataError()));

}

void NetworkManager::load_recent_balls(/*DLT_WIN_BALL *balls*/)
{
    // send the request to fetch for the recent win balls
    m_recent_win_balls_url = QUrl("http://f.apiplus.cn/dlt-20.json");
    QNetworkReply* reply = m_net_access_manager->get(QNetworkRequest(m_recent_win_balls_url));
}

void NetworkManager::handleNetworkReply(QNetworkReply *reply)
{
    QVariant statusCodeV =  reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    if(statusCodeV == 200)
    {
        QByteArray bytes = reply->readAll();
        //        QString data = QString::fromUtf8(bytes);
//        qDebug() << bytes;
        parse2RecentWinBallsData(bytes);

    }
    else
    {
        qDebug() << "Can not get the online win balls data";
        emit(fetchRecentWinBallsDataError()); // download failed
    }
}

void NetworkManager::hadleAuthenticationRequired(QNetworkReply *reply, QAuthenticator *authenticator)
{
    qDebug() << "hadleAuthenticationRequired";
}

void NetworkManager::handleEncrypted(QNetworkReply *reply)
{
    qDebug() << "handleEncrypted";
}

void NetworkManager::handleNetworkAccessibleChanged(QNetworkAccessManager::NetworkAccessibility accessible)
{
    qDebug() << "handleNetworkAccessibleChanged";
}

void NetworkManager::handlePreSharedKeyAuthenticationRequired(QNetworkReply *reply, QSslPreSharedKeyAuthenticator *authenticator)
{
    qDebug() << "handlePreSharedKeyAuthenticationRequired";
}

void NetworkManager::handleProxyAuthenticationRequired(const QNetworkProxy &proxy, QAuthenticator *authenticator)
{
    qDebug() << "handleProxyAuthenticationRequired";
}

void NetworkManager::handleSSLErrors(QNetworkReply *reply, const QList<QSslError> &errors)
{
    qDebug() << "handleSSLErrors";
}

void NetworkManager::parse2RecentWinBallsData(QByteArray byte)
{
    QJsonParseError json_error;
    QJsonDocument parse_doucment = QJsonDocument::fromJson(byte, &json_error);
    if(json_error.error == QJsonParseError::NoError)
    {
        if(parse_doucment.isObject())
        {
            QJsonObject obj = parse_doucment.object();
            if(obj.contains("data"))
            {
                QJsonValue data_value = obj.take("data");
                if(data_value.isArray())
                {
                    QJsonArray data_array = data_value.toArray();
                    QList<DLT_WIN_BALL_DATA>* balls = new QList<DLT_WIN_BALL_DATA>;
                    for(int i = 0; i < data_array.size(); i++)
                    {
                        QJsonObject obj = data_array.at(i).toObject();
//                        qDebug() << obj.take("expect").toString()
//                        << " " << obj.take("opencode").toString()
//                        << " "   << obj.take("opentime").toString()
//                        << " " << obj.take("opentimestamp").toInt();

                        DLT_WIN_BALL_DATA data;
                        data.expect = obj.take("expect").toString();
                        data.date = obj.take("opentime").toString();

                        // parsing the opencode
                        data.m_ball = parseWinBalls(obj.take("opencode").toString());
                        balls->append(data);
                    }
                    emit(fetchRecentWinBallsDataFinished(balls));
                }
                else
                {
                    emit(fetchRecentWinBallsDataError()); // parse failed
                }
            }

        }
    }
}

DLT_WIN_BALL NetworkManager::parseWinBalls(QString openCodeStr)
{
    // start to parse the opencode string to DLT_WIN_BALL_DATA data
    DLT_WIN_BALL data;
    QStringList red_blue_list = openCodeStr.split("+");
    QStringList red_list = ((QString)red_blue_list.at(0)).split(",");
    QStringList blue_list = ((QString)red_blue_list.at(1)).split(",");

    bool ok;
    for(int i = 0; i < red_list.size(); i++)
    {
        data.m_red[i] = (EDLT_RED_BALL)((QString)red_list[i]).toInt(&ok, 10);
    }
    for(int i = 0; i < blue_list.size(); i++)
    {
        data.m_blue[i] = (EDLT_BLUE_BALL)((QString)blue_list[i]).toInt(&ok, 10);
    }
    return data;
}

