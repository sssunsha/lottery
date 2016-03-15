#ifndef LOCALDATAMANAGER_H
#define LOCALDATAMANAGER_H

#include <QObject>
#include "constant.h"

class LocalDataManager : public QObject
{
    Q_OBJECT
public:
    LocalDataManager(QObject* parent = 0);
};

#endif // LOCALDATAMANAGER_H
