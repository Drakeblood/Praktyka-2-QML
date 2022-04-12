#include "include/PImageSaver.h"
#include "include/PImageModifierExecutor.h"

#include "QDebug"

PImageSaver::PImageSaver(QObject *parent)
    : QObject{parent}
    , pImageModifierExecutor(new PImageModifierExecutor(this))
    , mSaveCount(5)
    , saveIndex(0)
    , isConnected(false)
{
    connect(pImageModifierExecutor, &PImageModifierExecutor::finished, this, &PImageSaver::saveImage);
    cvImageInstances.push_back(cv::Mat());
}

PImageSaver::~PImageSaver()
{
    qDebug() << "PImageSaver destroyed.";
}

void PImageSaver::setCVImageInstanceReference(const cv::Mat *_cvImageInstanceReference)
{
    cvImageInstanceReference = _cvImageInstanceReference;
}

void PImageSaver::setupImageModifierExecutor(QVector<PImageModifierBase*> *_imageModifierOptionItems)
{
    pImageModifierExecutor->setupExecutor(_imageModifierOptionItems, &cvImageInstances);
}

void PImageSaver::saveImages()
{
    if(saveIndex < mSaveCount)
    {
        cvImageInstances[0] = cvImageInstanceReference->clone();
        if(!cvImageInstances[0].empty())
        {
            if(!isConnected)
            {
                isConnected = connect(pImageModifierExecutor, &PImageModifierExecutor::finished, this, &PImageSaver::saveImages);
            }
            pImageModifierExecutor->executeModifiers();
            saveIndex++;
            qDebug() << saveIndex;
        }
    }
    else
    {
        isConnected = !disconnect(pImageModifierExecutor, &PImageModifierExecutor::finished, this, &PImageSaver::saveImages);
        saveIndex = 0;
    }
}

void PImageSaver::setSaveCount(const QVariant &newSaveCount)
{
    auto saveCountInt = newSaveCount.toInt();
    if(mSaveCount != saveCountInt)
    {
        mSaveCount = saveCountInt;
    }
}

QString PImageSaver::saveLocation() const
{
    return mSaveLocation.c_str();
}

void PImageSaver::setSaveLocation(const QString &newSaveLocation)
{
    std::string stdStrPath = newSaveLocation.toStdString();
    stdStrPath = stdStrPath.substr(8);

    mSaveLocation = stdStrPath;
}

void PImageSaver::saveImage()
{
    std::string filepath = mSaveLocation + "/generated_image_";
    filepath += std::to_string(saveIndex);
    filepath += ".jpg";

    cv::imwrite(filepath, cvImageInstances[0]);
    qDebug() << "File saved";
}

unsigned int PImageSaver::saveCount() const
{
    return mSaveCount;
}
