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
    QStringList paramNames;

public:
    PImageModifierBase();

    virtual void transform(cv::Mat *src, cv::Mat *dst, QStringList stringParams) = 0;

    const QStringList& getParamNames() const;
};

#endif // PIMAGEMODIFIERBASE_H
