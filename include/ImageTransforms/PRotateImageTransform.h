#ifndef PROTATEIMAGETRANSFORM_H
#define PROTATEIMAGETRANSFORM_H

#include "PImageTransformBase.h"

class PRotateImageTransform : public PImageTransformBase
{
public:
    PRotateImageTransform();

    virtual void transform(QVariant args...) override;
};

#endif // PROTATEIMAGETRANSFORM_H
