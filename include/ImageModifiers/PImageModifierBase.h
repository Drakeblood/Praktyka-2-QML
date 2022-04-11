#ifndef PIMAGEMODIFIERBASE_H
#define PIMAGEMODIFIERBASE_H

#include <QVariant>
#include <QStringList>
#include <QDebug>

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"

/** Base class for image modifiers */
class PImageModifierBase : public QObject
{
    Q_OBJECT
protected:
    QString text;
    QMap<QString, QVariant> paramsMap;

public:
    PImageModifierBase();
    virtual ~PImageModifierBase();
    PImageModifierBase(const PImageModifierBase &pImageModifierBase);

    virtual PImageModifierBase* clone() const = 0;
    virtual void transform(cv::Mat *src, cv::Mat *dst) = 0;

    QString getText() const;
    const QMap<QString, QVariant>* getParamsMap() const;

    void setParameter(QString paramKey, QVariant paramValue);

    static double fRand(const double fMin, const double fMax);

};

#endif // PIMAGEMODIFIERBASE_H
