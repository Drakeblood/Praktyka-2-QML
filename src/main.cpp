#include "include/PImageStreamer.h"
#include "include/PImageProvider.h"
#include "include/PImageSaver.h"
#include "include/PImageModifierExecutor.h"
#include "include/PEditableImageModifierListModel.h"
#include "include/PEditableImageModifierList.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtConcurrent/QtConcurrent>

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

    PImageModifierExecutor livePreviewImageModifierExecutor;
    livePreviewImageModifierExecutor.setupExecutor(&(editableImageModifierList.mChosenModifiers), imageProvider->imageStreamer->getCVImageInstances());
    QObject::connect(&livePreviewImageModifierExecutor, &PImageModifierExecutor::preExecuteModifiers, imageProvider->imageStreamer, &PImageStreamer::resetCVImageInstances);
    QObject::connect(&livePreviewImageModifierExecutor,
                     &PImageModifierExecutor::finished,
                     imageProvider->imageStreamer,
                     [&imageProvider] () { QtConcurrent::run(imageProvider->imageStreamer, &PImageStreamer::updateQImages); }
    );
    engine.rootContext()->setContextProperty(QStringLiteral("livePreviewImageModifierExecutor"), &livePreviewImageModifierExecutor);

    PImageSaver imageSaver;
    imageSaver.setCVImageInstanceReference(imageProvider->imageStreamer->getCVImageInstanceOriginal());
    imageSaver.setupImageModifierExecutor(&(editableImageModifierList.mChosenModifiers));
    engine.rootContext()->setContextProperty(QStringLiteral("imageSaver"), &imageSaver);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
