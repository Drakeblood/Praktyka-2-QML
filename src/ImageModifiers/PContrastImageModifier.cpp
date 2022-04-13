#include "include/ImageModifiers/PContrastImageModifier.h"

PContrastImageModifier::PContrastImageModifier()
{
    text = "Contrast";
    paramsMap.insert("Min", 0.4);
    paramsMap.insert("Max", 2);
}

PContrastImageModifier::~PContrastImageModifier()
{
    qDebug() << "PContrastImageModifier destroyed.";
}

PContrastImageModifier::PContrastImageModifier(const PContrastImageModifier &pContrastImageModifier)
    : PImageModifierBase(pContrastImageModifier)
{

}

PImageModifierBase *PContrastImageModifier::clone() const
{
    return new PContrastImageModifier(*this);
}

void PContrastImageModifier::transform(cv::Mat *src, cv::Mat *dst)
{
    qDebug() << "Contrast image modifier";

    double contrast = fRand(paramsMap["Min"].toDouble(), paramsMap["Max"].toDouble());

    dst->convertTo(*src, -1, contrast);
}
