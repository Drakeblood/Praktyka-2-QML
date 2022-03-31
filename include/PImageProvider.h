#ifndef PIMAGEPROVIDER_H
#define PIMAGEPROVIDER_H

#include <QQuickImageProvider>

class PImageStreamer;

class PImageProvider : public QQuickImageProvider
{
public:
    PImageStreamer *imageStreamer;

public:
    PImageProvider();
    virtual ~PImageProvider();

    virtual QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize) override;

};

#endif // PIMAGEPROVIDER_H
