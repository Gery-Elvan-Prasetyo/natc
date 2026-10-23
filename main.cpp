#include <QCoreApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QObject>
#include <cstdlib>
#include "SystemStatus.h"
#include <QQmlContext>

int main(int argc, char *argv[])
{
    qputenv("QT_WAYLAND_SHELL_INTEGRATION", "layer-shell");

    QGuiApplication app(argc, argv);
    app.setApplicationName("Serpantinum Native");
    app.setApplicationVersion("0.1.0");

    QQmlApplicationEngine engine;
    SystemStatus systemStatus;
engine.rootContext()->setContextProperty(
    "systemStatus", &systemStatus);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(EXIT_FAILURE); },
        Qt::QueuedConnection
    );

    engine.loadFromModule("Serpantinum", "Main");
    return app.exec();
}
