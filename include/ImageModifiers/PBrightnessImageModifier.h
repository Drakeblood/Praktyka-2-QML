#ifndef PBRIGHTNESSIMAGEMODIFIER_H
#define PBRIGHTNESSIMAGEMODIFIER_H

#include "PImageModifierBase.h"

class PBrightnessImageModifier : public PImageModifierBase
{
public:
    PBrightnessImageModifier();
    virtual ~PBrightnessImageModifier();
    PBrightnessImageModifier(const PBrightnessImageModifier &pContrastImageModifier);

    virtual PImageModifierBase* clone() const override;
    virtual void transform(cv::Mat *src, cv::Mat *dst) override;
};

#endif // PBRIGHTNESSIMAGEMODIFIER_H
