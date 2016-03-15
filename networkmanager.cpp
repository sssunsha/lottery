#include "networkmanager.h"
#include <QLoggingCategory>

NetworkManager::NetworkManager(QObject* parent)
    :QObject(parent)
{
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

    // send the request to fetch for the recent win balls
    m_recent_win_balls_url = QUrl("http://f.apiplus.cn/dlt-20.json");
    QNetworkReply* reply = m_net_access_manager->get(QNetworkRequest(m_recent_win_balls_url));
}

void NetworkManager::load_recent_balls(DLT_WIN_BALL *balls)
{

}

void NetworkManager::handleNetworkReply(QNetworkReply *reply)
{
    QVariant statusCodeV =  reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    if(statusCodeV == 200)
    {
        QByteArray bytes = reply->readAll();
        QString string = QString::fromUtf8(bytes);
        qDebug() << string;
    }
    else
    {
        qDebug() << "Can not get the online win balls data";
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

