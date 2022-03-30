#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "include/PImageStreamer.h"
#include "include/PImageProvider.h"
#include "include/PImageTransformationModel.h"
#include "include/PImageTransformationList.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    app.setOrganizationName("Some Company");
    app.setOrganizationDomain("somecompany.com");
    app.setApplicationName("Application");

    //qmlRegisterType<PImageStreamer>("Praktyka.ImageStreamer", 1, 0, "ImageStreamer");
    qmlRegisterType<PImageTransformationModel>("Praktyka.ImageTransformation", 1, 0, "ImageTransformationModel");

    qmlRegisterUncreatableType<PImageTransformationList>("Praktyka.ImageTransformation", 1, 0, "ImageTransformationList",
    QStringLiteral("ToDoList should not be created in QML"));

    QQmlApplicationEngine engine;

    PImageTransformationList imageTransformationList;
    engine.rootContext()->setContextProperty(QStringLiteral("imageTransformationList"), &imageTransformationList);

    PImageStreamer imageStreamer;
    engine.rootContext()->setContextProperty(QStringLiteral("imageStreamer"), &imageStreamer);

    PImageProvider *imageProvider = new PImageProvider;
    engine.addImageProvider(QStringLiteral("imageProvider"), imageProvider);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
