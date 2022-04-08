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
