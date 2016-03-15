#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>
#include <QString>
#include <QUrl>
#include "constant.h"
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>

class NetworkManager : public QObject
{
    Q_OBJECT
public:
    NetworkManager(QObject* parent = 0);
    void load_recent_balls(/*DLT_WIN_BALL* balls*/);
signals:
    void fetchRecentWinBallsDataFinished();
    void fetchRecentWinBallsDataError();

private slots:
void handleNetworkReply(QNetworkReply* reply);
void hadleAuthenticationRequired(QNetworkReply * reply, QAuthenticator * authenticator);
void handleEncrypted(QNetworkReply * reply);
void handleNetworkAccessibleChanged(QNetworkAccessManager::NetworkAccessibility accessible);
void handlePreSharedKeyAuthenticationRequired(QNetworkReply * reply, QSslPreSharedKeyAuthenticator * authenticator);
void handleProxyAuthenticationRequired(const QNetworkProxy & proxy, QAuthenticator * authenticator);
void handleSSLErrors(QNetworkReply * reply, const QList<QSslError> & errors);

private:
    void parse2RecentWinBallsData(QByteArray byte);

    QNetworkAccessManager* m_net_access_manager;
    QUrl m_recent_win_balls_url;
};

#endif // NETWORKMANAGER_H
