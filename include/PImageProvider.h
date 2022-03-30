#ifndef PIMAGEPROVIDER_H
#define PIMAGEPROVIDER_H

#include <QQuickImageProvider>

#include "include/PImageStreamer.h"

class PImageProvider : public QQuickImageProvider
{
private:
    //PImageStreamer imageStreamer;


public:
    PImageProvider();
    ~PImageProvider();

    virtual QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize) override;

};

#endif // PIMAGEPROVIDER_H
