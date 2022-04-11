#include "include/PImageStreamer.h"
#include "include/PImageProvider.h"
#include "include/PImageModifierExecutor.h"
#include "include/PEditableImageModifierListModel.h"
#include "include/PEditableImageModifierList.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    app.setOrganizationName("Some Company");
    app.setOrganizationDomain("somecompany.com");
    app.setApplicationName("Application");

    qmlRegisterType<PEditableImageModifierListModel>("Praktyka.ImageModifiers", 1, 0, "EditableImageModifierListModel");

    qmlRegisterUncreatableType<PEditableImageModifierList>("Praktyka.ImageModifiers", 1, 0, "EditableImageModifierList",
    QStringLiteral("EditableImageModifierList should not be created in QML"));

    QQmlApplicationEngine engine;

    PEditableImageModifierList editableImageModifierList;
    engine.rootContext()->setContextProperty(QStringLiteral("editableImageModifierList"), &editableImageModifierList);

    PImageProvider *imageProvider = new PImageProvider;
    engine.addImageProvider(QStringLiteral("imageProvider"), imageProvider);
    engine.rootContext()->setContextProperty(QStringLiteral("imageStreamer"), imageProvider->imageStreamer);

    PImageModifierExecutor imageModifierExecutor;
    imageModifierExecutor.setupExecutor(&(editableImageModifierList.mChosenModifiers), imageProvider->imageStreamer);
    engine.rootContext()->setContextProperty(QStringLiteral("imageModifierExecutor"), &imageModifierExecutor);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
