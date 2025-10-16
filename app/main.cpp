#include <QApplication>
#include <QQmlApplicationEngine>

#include <config.hpp>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("dynamic_qml_component/app", "Main");

    return app.exec();
}
