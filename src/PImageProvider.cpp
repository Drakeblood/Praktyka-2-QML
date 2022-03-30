#include "include/PImageProvider.h"
#include "QDebug"

PImageProvider::PImageProvider()
    : QQuickImageProvider(QQuickImageProvider::Image)
{

}

PImageProvider::~PImageProvider()
{
    qDebug() << "Image Provider destroyed.";
}

QImage PImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    QImage image;
    image.load("C:/Users/PC/Desktop/moodboard.png");
    return image;
}
