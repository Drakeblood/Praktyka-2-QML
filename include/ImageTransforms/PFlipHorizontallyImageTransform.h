#ifndef PFLIPHORIZONTALLYIMAGETRANSFORM_H
#define PFLIPHORIZONTALLYIMAGETRANSFORM_H

#include <include/ImageTransforms/PImageTransformBase.h>

class PFlipHorizontallyImageTransform : public PImageTransformBase
{
public:
    PFlipHorizontallyImageTransform();

    virtual void transform(QVariant args...) override;
};

#endif // PFLIPHORIZONTALLYIMAGETRANSFORM_H
