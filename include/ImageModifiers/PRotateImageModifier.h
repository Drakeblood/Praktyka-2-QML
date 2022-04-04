#ifndef PROTATEIMAGEMODIFIER_H
#define PROTATEIMAGEMODIFIER_H

#include "include/ImageModifiers/PImageModifierBase.h"

class PRotateImageModifier : public PImageModifierBase
{
public:
    PRotateImageModifier();

    virtual void transform(QVariant args...) override;
};

#endif // PROTATEIMAGEMODIFIER_H
