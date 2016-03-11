#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>

class NetworkManager : public QObject
{
    Q_OBJECT
public:
    NetworkManager(QObject* parent = 0);
};

#endif // NETWORKMANAGER_H
