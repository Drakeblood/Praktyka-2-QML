#include "include/PImageProvider.h"

PImageProvider::PImageProvider()
    : QQuickImageProvider(QQuickImageProvider::Pixmap)
    , Width(200)
    , Height(100)
{

}

QImage PImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    return QImage();
}
