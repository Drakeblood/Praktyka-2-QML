#include "include/ImageModifiers/PBrightnessImageModifier.h"

PBrightnessImageModifier::PBrightnessImageModifier()
{
    text = "Brightness";
    paramsMap.insert("Min", -20);
    paramsMap.insert("Max", 20);
}

PBrightnessImageModifier::~PBrightnessImageModifier()
{
    qDebug() << "PBrightnessImageModifier destroyed.";
}

PBrightnessImageModifier::PBrightnessImageModifier(const PBrightnessImageModifier &pBrightnessImageModifier)
    : PImageModifierBase(pBrightnessImageModifier)
{

}

PImageModifierBase *PBrightnessImageModifier::clone() const
{
    return new PBrightnessImageModifier(*this);
}

void PBrightnessImageModifier::transform(cv::Mat *src, cv::Mat *dst)
{
    qDebug() << "Brightness image modifier";

    double brightness = fRand(paramsMap["Min"].toDouble(), paramsMap["Max"].toDouble());

    dst->convertTo(*src, -1, 1, brightness);
}
