#include "include/PImageStreamer.h"
#include "QDebug"

PImageStreamer::PImageStreamer(QObject *parent)
    : QObject{parent}
{

}

void PImageStreamer::loadImage()
{
    cvImageInstance = cv::imread(imageLocationNative.toStdString());
    qImageInstanceNative = QImage(cvImageInstance.data, cvImageInstance.cols, cvImageInstance.rows, cvImageInstance.step, QImage::Format_A2BGR30_Premultiplied);
}

QImage PImageStreamer::qImageInstance() const
{
    qDebug() << "TESTTSTSTSTST";
    return qImageInstanceNative;
}

QString PImageStreamer::imageLocation() const
{
    return imageLocationNative;
}

void PImageStreamer::setImageLocation(const QString newImageLocation)
{
    if(imageLocationNative != newImageLocation)
    {
        imageLocationNative = newImageLocation;
        loadImage();
        emit imageLocationChanged();
    }
}
