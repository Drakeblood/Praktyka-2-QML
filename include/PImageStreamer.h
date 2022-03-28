#ifndef PIMAGESTREAMER_H
#define PIMAGESTREAMER_H

#include <QObject>

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2\core\core.hpp"

class PImageStreamer : public QObject
{
    Q_OBJECT
public:
    explicit PImageStreamer(QObject *parent = nullptr);

    void LoadImage();

signals:

};

#endif // PIMAGESTREAMER_H
