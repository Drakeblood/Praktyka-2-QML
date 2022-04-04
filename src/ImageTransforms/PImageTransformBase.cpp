#include "include/ImageTransforms/PImageTransformBase.h"
#include "QDebug"

PImageTransformBase::PImageTransformBase()
{

}

const QStringList& PImageTransformBase::getParamNames() const
{
    return paramNames;
}
