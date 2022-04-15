#include "include/ImageModifiers/PGaussianBlurImageModifier.h"


PGaussianBlurImageModifier::PGaussianBlurImageModifier()
{
    text = "Gaussian Blur";
    paramsMap.insert("Width/Height min", 3);
    paramsMap.insert("Width/Height max", 3);
}

PGaussianBlurImageModifier::~PGaussianBlurImageModifier()
{
    qDebug() << "PGaussianBlurImageModifier destroyed.";
}

PGaussianBlurImageModifier::PGaussianBlurImageModifier(const PGaussianBlurImageModifier &pGaussianBlurImageModifier)
    : PImageModifierBase(pGaussianBlurImageModifier)
{

}

PImageModifierBase* PGaussianBlurImageModifier::clone() const
{
    return new PGaussianBlurImageModifier(*this);
}

void PGaussianBlurImageModifier::transform(cv::Mat *src, cv::Mat *dst)
{
    qDebug() << "Gaussian Blur image modifier";

    int size = fRand(paramsMap["Width/Height min"].toInt(), paramsMap["Width/Height max"].toInt());
    if(!isOdd(size))
    {
        size++;//only odd
    }
    cv::GaussianBlur(*src, *dst, cv::Size(size, size), 0);
}
