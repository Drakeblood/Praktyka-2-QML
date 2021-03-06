#ifndef PIMAGESTREAMER_H
#define PIMAGESTREAMER_H

#include "include/PImageModifierExecutor.h"

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

    cv::Mat cvImageInstanceOriginal;

    QVector<cv::Mat> cvImageInstances;
    QVector<QImage> qImageInstances;

public:
    explicit PImageStreamer(QObject *parent = nullptr);
    virtual ~PImageStreamer();

    Q_INVOKABLE
    void loadImage(const QString& imagePath);

    void convertCVMatToQImage(int index);
    void updateQImages();
    void resetCVImageInstances();

    const cv::Mat* getCVImageInstanceOriginal() const;
    QVector<cv::Mat>* getCVImageInstances();
    QImage* getQImage(int index);

signals:
    void qImagesUpdated();

    //friend class PImageModifierExecutor;

};

#endif // PIMAGESTREAMER_H
