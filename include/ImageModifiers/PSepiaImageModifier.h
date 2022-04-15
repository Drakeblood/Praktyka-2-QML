#ifndef PSEPIAIMAGEMODIFIER_H
#define PSEPIAIMAGEMODIFIER_H

#include "include/ImageModifiers/PImageModifierBase.h"

class PSepiaImageModifier : public PImageModifierBase
{
public:
    PSepiaImageModifier();
    virtual ~PSepiaImageModifier();
    PSepiaImageModifier(const PSepiaImageModifier &pSepiaImageModifier);

    virtual PImageModifierBase* clone() const override;
    virtual void transform(cv::Mat *src, cv::Mat *dst) override;
};

#endif // PSEPIAIMAGEMODIFIER_H
