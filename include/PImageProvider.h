#ifndef PIMAGEPROVIDER_H
#define PIMAGEPROVIDER_H

#include <QQuickImageProvider>

#include "include/PImageStreamer.h"

class PImageProvider : public QQuickImageProvider
{
public:
    int Width;
    int Height;

private:
    PImageStreamer ImageStreamer;

public:
    PImageProvider();

    virtual QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize) override;

};

#endif // PIMAGEPROVIDER_H
