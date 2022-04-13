#ifndef PCONTRASTIMAGEMODIFIER_H
#define PCONTRASTIMAGEMODIFIER_H

#include "PImageModifierBase.h"

class PContrastImageModifier : public PImageModifierBase
{
public:
    PContrastImageModifier();
    virtual ~PContrastImageModifier();
    PContrastImageModifier(const PContrastImageModifier &pContrastImageModifier);

    virtual PImageModifierBase* clone() const override;
    virtual void transform(cv::Mat *src, cv::Mat *dst) override;
};

#endif // PCONTRASTIMAGEMODIFIER_H
