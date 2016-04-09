#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QQuickWindow>
#include "dltwinballmanager.h"

QApplication* global_app;

static QObject *provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);

    DLTWINBallManager * p = new DLTWINBallManager(global_app);
    QQmlEngine::setObjectOwnership(p, QQmlEngine::CppOwnership);
    return p;
}



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    global_app = &app;
    qmlRegisterSingletonType<DLTWINBallManager>("DLTManager", 1, 0, "DLTManager", provider);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));    

    return app.exec();
}

