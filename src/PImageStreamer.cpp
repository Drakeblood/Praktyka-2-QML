#include "include/PImageStreamer.h"

#include "QDebug"

PImageStreamer::PImageStreamer(QObject *parent)
    : QObject{parent}
{

}

void PImageStreamer::loadImage(const QString& imagePath)
{
    std::string stdStrPath = imagePath.toStdString();
    stdStrPath = stdStrPath.substr(8);

    cvImageInstance = cv::imread(stdStrPath);

    if(cvImageInstance.empty())
    {
        qDebug() << "Load image failed.";
    }
}

void PImageStreamer::convertCVMatToQImage()
{
    if(!cvImageInstance.empty())
    {
        qImageInstance = QImage(
                    (uchar*) cvImageInstance.data,
                    cvImageInstance.cols,
                    cvImageInstance.rows,
                    cvImageInstance.step,
                    QImage::Format_RGB888
                    ).rgbSwapped();
    }
    else
    {
        qDebug() << "Convert image failed.";
    }
}

QImage* PImageStreamer::getQImage()
{
    convertCVMatToQImage();
    return &qImageInstance;
}
