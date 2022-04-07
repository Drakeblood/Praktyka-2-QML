#include "include/ImageModifiers/PFlipHorizontallyImageModifier.h"

PFlipHorizontallyImageModifier::PFlipHorizontallyImageModifier()
{

}

void PFlipHorizontallyImageModifier::transform(cv::Mat *src, cv::Mat *dst, QStringList stringParams)
{
    qDebug() << "Flip image modifier";

    cv::flip(*src, *dst, 1);
}
