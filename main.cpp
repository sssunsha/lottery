#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "dltwinballmanager.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    DLTWINBallManager* wbm = new DLTWINBallManager(&app);
    if(!wbm->init()) return -1;

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}

