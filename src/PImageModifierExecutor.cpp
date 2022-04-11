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

void PImageModifierExecutor::setupExecutor(QVector<PImageModifierBase*>* _imageModifierOptionItems, QVector<cv::Mat>* _cvImageInstances)
{
    imageModifierOptionItems = _imageModifierOptionItems;
    cvImageInstances = _cvImageInstances;

    int count = cvImageInstances->size();
    futureWatchers.reserve(count);

    for(int i = 0; i < count; i++)
    {
        futureWatchers.push_back(new QFutureWatcher<void>(this));
    }
}

void PImageModifierExecutor::executeModifiers()
{
    if( !((*cvImageInstances)[0].empty()) )
    {
        emit preExecuteModifiers();

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
    for(int i = 0; i < futureWatchers.size(); i++)
    {
        futureWatchers[i]->setFuture(QtConcurrent::run(this, &PImageModifierExecutor::executeModifiers, i));
        futureWatchers[i]->waitForFinished();
    }
}

void PImageModifierExecutor::executeModifiers(int index)
{
    for(int i = 0; i < imageModifierOptionItems->size(); i++)
    {
        qDebug() << "FutureWatcher " << index;

        (*imageModifierOptionItems)[i]->transform(
                    &((*cvImageInstances)[index]),
                    &((*cvImageInstances)[index])
                    );
    }
}
