#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "include/PImageProvider.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication App(argc, argv);

    App.setOrganizationName("Some Company");
    App.setOrganizationDomain("somecompany.com");
    App.setApplicationName("Application");

    QQmlApplicationEngine Engine;

    Engine.addImageProvider(QLatin1String("loadedImage"), new PImageProvider);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&Engine, &QQmlApplicationEngine::objectCreated,
                     &App, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    Engine.load(url);

    return App.exec();
}
