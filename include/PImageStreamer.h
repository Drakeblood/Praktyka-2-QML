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
    Q_PROPERTY(QString imageLocation READ imageLocation WRITE setImageLocation NOTIFY imageLocationChanged)
    Q_PROPERTY(QImage qImageInstance READ qImageInstance NOTIFY qImageInstanceChanged)

public:
    QString imageLocationNative;
    QImage qImageInstanceNative;

private:
    cv::Mat cvImageInstance;

public:
    explicit PImageStreamer(QObject *parent = nullptr);

    void loadImage();


signals:
    void imageLocationChanged();
    void qImageInstanceChanged();

private:
    QString imageLocation() const;
    void setImageLocation(const QString newImageLocation);

    QImage qImageInstance() const;

};

#endif // PIMAGESTREAMER_H
