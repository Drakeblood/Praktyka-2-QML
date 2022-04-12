#ifndef PIMAGESAVER_H
#define PIMAGESAVER_H

#include <QObject>

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"

class PImageModifierExecutor;
class PImageModifierBase;

class PImageSaver : public QObject
{
    Q_OBJECT
    Q_PROPERTY(unsigned int saveCount READ saveCount WRITE setSaveCount)
    Q_PROPERTY(QString saveLocation READ saveLocation WRITE setSaveLocation)

private:
    PImageModifierExecutor *pImageModifierExecutor;

    const cv::Mat *cvImageInstanceReference;
    QVector<cv::Mat> cvImageInstances;

    unsigned int mSaveCount;
    std::string mSaveLocation;

    unsigned int saveIndex;

    bool isConnected;

public:
    explicit PImageSaver(QObject *parent = nullptr);
    virtual ~PImageSaver();

    void setCVImageInstanceReference(const cv::Mat* _cvImageInstanceReference);
    void setupImageModifierExecutor(QVector<PImageModifierBase*> *_imageModifierOptionItems);

public slots:
    void saveImages();

private:
    unsigned int saveCount() const;
    void setSaveCount(const QVariant &newSaveCount);

    QString saveLocation() const;
    void setSaveLocation(const QString &newSaveLocation);

    void saveImage();

};

#endif // PIMAGESAVER_H
