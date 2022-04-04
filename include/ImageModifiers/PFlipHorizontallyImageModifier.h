#ifndef PFLIPHORIZONTALLYIMAGEMODIFIER_H
#define PFLIPHORIZONTALLYIMAGEMODIFIER_H

#include <include/ImageModifiers/PImageModifierBase.h>

class PFlipHorizontallyImageModifier : public PImageModifierBase
{
public:
    PFlipHorizontallyImageModifier();

    virtual void transform(QVariant args...) override;
};

#endif // PFLIPHORIZONTALLYIMAGEMODIFIER_H
