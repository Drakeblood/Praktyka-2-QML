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

void PImageSaver::setSaveCount(unsigned int newSaveCount)
{
    if(mSaveCount != newSaveCount)
    {
        mSaveCount = newSaveCount;
    }
}

void PImageSaver::saveImage()
{
    std::string filename = "generated_image_";
    filename += std::to_string(saveIndex);
    filename += ".jpg";

    cv::imwrite(filename, cvImageInstances[0]);
    qDebug() << "File saved";
}

unsigned int PImageSaver::saveCount()
{
    return mSaveCount;
}
