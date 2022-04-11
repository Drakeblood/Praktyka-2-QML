#include "include/ImageModifiers/PImageModifierBase.h"
#include "QDebug"

PImageModifierBase::PImageModifierBase()
{

}

PImageModifierBase::~PImageModifierBase()
{

}

PImageModifierBase::PImageModifierBase(const PImageModifierBase &pImageModifierBase)
    : text(pImageModifierBase.text)
    , paramsMap(pImageModifierBase.paramsMap)
{

}

QString PImageModifierBase::getText() const
{
    return text;
}

const QMap<QString, QVariant>* PImageModifierBase::getParamsMap() const
{
    return &paramsMap;
}

void PImageModifierBase::setParameter(QString paramKey, QVariant paramValue)
{
    paramsMap[paramKey] = paramValue;
}

double PImageModifierBase::fRand(const double fMin, const double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}
