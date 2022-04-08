#include "include/ImageModifiers/PGaussianBlurImageModifier.h"


PGaussianBlurImageModifier::PGaussianBlurImageModifier()
{
    text = "Gaussian Blur";
    paramsMap.insert("Width", 3);
    paramsMap.insert("Height", 3);
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
    qDebug() << "GaussianBlur image modifier";

    cv::GaussianBlur(*src, *dst, cv::Size(5, 5), 0);
}
