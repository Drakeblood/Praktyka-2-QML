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
    int imageCount;

    QVector<cv::Mat> cvImageInstances;
    QVector<QImage> qImageInstances;

public:
    explicit PImageStreamer(QObject *parent = nullptr);

    Q_INVOKABLE
    void loadImage(const QString& imagePath, int index);

    void convertCVMatToQImage(int index);

    QImage* getQImage(int index);


};

#endif // PIMAGESTREAMER_H
