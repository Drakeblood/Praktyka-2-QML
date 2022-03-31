#include "include/PImageProvider.h"
#include "include/PImageStreamer.h"

#include "QDebug"

#include "opencv2/core.hpp"

PImageProvider::PImageProvider()
    : QQuickImageProvider(QQuickImageProvider::Image)
    , imageStreamer(new PImageStreamer)
{

}

PImageProvider::~PImageProvider()
{
    delete imageStreamer;
}

QImage PImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    int index = id[0].unicode() - 48;
    qDebug() << "requestImage called." << index;

    QImage *qImage = imageStreamer->getQImage(index);
    if(qImage)
    {
        return *qImage;
    }
    return QImage();
}
