#include "include/PImageStreamer.h"

#include "QDebug"

PImageStreamer::PImageStreamer(QObject *parent)
    : QObject{parent}
    , imageCount (2)
    , cvImageInstances(imageCount)
    , qImageInstances(imageCount)
{
    for(int i = 0; i <imageCount; i++)
    {
        cvImageInstances[i] = cv::Mat();
        qImageInstances[i] = QImage();
    }

}

void PImageStreamer::loadImage(const QString& imagePath, int index)
{
    if(index < cvImageInstances.size())
    {
        std::string stdStrPath = imagePath.toStdString();
        stdStrPath = stdStrPath.substr(8);

        cvImageInstances[index] = cv::imread(stdStrPath);

        if(cvImageInstances[index].empty())
        {
            qDebug() << "Load image failed.";
        }
    }
    else
    {
        qDebug() << "Load image failed - not valid index.";
    }
}

void PImageStreamer::convertCVMatToQImage(int index)
{
    if(index < cvImageInstances.size() && !cvImageInstances[index].empty())
    {
        auto cvImageInstance = cvImageInstances[index];
        qImageInstances[index] = QImage(
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

QImage* PImageStreamer::getQImage(int index)
{
    if(index < cvImageInstances.size())
    {
        convertCVMatToQImage(index);
        return &(qImageInstances[index]);
    }
    return nullptr;
}
