#include "include/ImageModifiers/PGaussianBlurImageModifier.h"

PGaussianBlurImageModifier::PGaussianBlurImageModifier()
{

}

void PGaussianBlurImageModifier::transform(cv::Mat *src, cv::Mat *dst, QStringList stringParams)
{
    qDebug() << "GaussianBlur image modifier";

    cv::GaussianBlur(*src, *dst, cv::Size(5, 5), 0);
}
