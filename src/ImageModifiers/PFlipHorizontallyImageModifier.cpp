#include "include/ImageModifiers/PFlipHorizontallyImageModifier.h"
#include "QDebug"

PFlipHorizontallyImageModifier::PFlipHorizontallyImageModifier()
{

}

void PFlipHorizontallyImageModifier::transform(cv::Mat *src, cv::Mat *dst, QStringList stringParams)
{
    qDebug() << "flip";
    cv::flip(*src, *dst, 1);
}
