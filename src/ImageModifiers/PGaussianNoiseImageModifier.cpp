#include "include/ImageModifiers/PGaussianNoiseImageModifier.h"

PGaussianNoiseImageModifier::PGaussianNoiseImageModifier()
{
    text = "Gaussian Noise";
    paramsMap.insert("Min", 3);
    paramsMap.insert("Max", 5);
}

PGaussianNoiseImageModifier::~PGaussianNoiseImageModifier()
{
    qDebug() << "PGaussianBlurImageModifier destroyed.";
}

PGaussianNoiseImageModifier::PGaussianNoiseImageModifier(const PGaussianNoiseImageModifier &pGaussianNoiseImageModifier)
    : PImageModifierBase(pGaussianNoiseImageModifier)
{

}

PImageModifierBase* PGaussianNoiseImageModifier::clone() const
{
    return new PGaussianNoiseImageModifier(*this);
}

void PGaussianNoiseImageModifier::transform(cv::Mat *src, cv::Mat *dst)
{
    qDebug() << "Gaussian Noise image modifier";

    int size = fRand(paramsMap["Min"].toDouble(), paramsMap["Max"].toDouble());
    cv::Mat noise(src->size(),src->type());
    cv::randn(noise, size, size);
    *dst += noise;
}
