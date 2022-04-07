#include "include/PImageStreamer.h"
#include "include/PImageModifierExecutor.h"
#include "include/ImageModifiers/PImageModifierBase.h"

#include "QDebug"

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"

PImageModifierExecutor::PImageModifierExecutor(QObject *parent)
    : QThread{parent}
    , executeCounter(0)
{

}

PImageModifierExecutor::~PImageModifierExecutor()
{
    qDebug() << "PImageModifierExecutor destroyed.";
}

void PImageModifierExecutor::setupExecutor(QVector<ImageModifierOptionItem> *_imageModifierOptionItems, QVector<PImageModifierBase *> *_modifierList, PImageStreamer* _imageStreamer)
{
    imageModifierOptionItems = _imageModifierOptionItems;
    modifierList = _modifierList;
    imageStreamer = _imageStreamer;

    connect(this, &PImageModifierExecutor::finished, imageStreamer, &PImageStreamer::updateQImages);

    int count = imageStreamer->imageCount;
    futureWatchers.reserve(count);

    for(int i = 0; i < count; i++)
    {
        futureWatchers.push_back(new QFutureWatcher<void>(this));
    }
}

void PImageModifierExecutor::executeModifiers()
{
    if(!imageStreamer->cvImageInstanceOriginal.empty())
    {
        start();
        qDebug() << "Modifiers executor started - execute count: " << ++executeCounter;
    }
    else
    {
        qDebug() << "No image loaded";
    }
}

void PImageModifierExecutor::run()
{
    imageStreamer->resetCVImageInstances();

    for(int i = 0; i < imageStreamer->imageCount; i++)
    {
        futureWatchers[i]->setFuture(QtConcurrent::run(this, &PImageModifierExecutor::executeModifiers, i));
        futureWatchers[i]->waitForFinished();
    }
}

void PImageModifierExecutor::executeModifiers(int index)
{
    if(index >= (*modifierList).size())
    {
        qDebug() << "Not valid index - update modifiers array in PImageModifierList" << index;
        return;
    }

    for(int i = 0; i < imageModifierOptionItems->size(); i++)
    {
        qDebug() << "FutureWatcher " << index;

        (*modifierList)[(*imageModifierOptionItems)[i].modifierIndex]->transform(
                    &(imageStreamer->cvImageInstances[index]),
                    &(imageStreamer->cvImageInstances[index]),
                    QStringList()
                    );
    }
}
