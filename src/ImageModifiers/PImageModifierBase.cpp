#include "include/ImageModifiers/PImageModifierBase.h"
#include "QDebug"

PImageModifierBase::PImageModifierBase()
{

}

const QStringList& PImageModifierBase::getParamNames() const
{
    return paramNames;
}
