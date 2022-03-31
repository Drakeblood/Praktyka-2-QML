#ifndef PIMAGESTREAMER_H
#define PIMAGESTREAMER_H

#include <QObject>
#include <QImage>

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"

class PImageStreamer : public QObject
{
    Q_OBJECT

private:
    cv::Mat cvImageInstance;
    QImage qImageInstance;

public:
    explicit PImageStreamer(QObject *parent = nullptr);

    Q_INVOKABLE
    void loadImage(const QString& imagePath);

    void convertCVMatToQImage();

    QImage* getQImage();


};

#endif // PIMAGESTREAMER_H
