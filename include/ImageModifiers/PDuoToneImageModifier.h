#ifndef PDUOTONEIMAGEMODIFIER_H
#define PDUOTONEIMAGEMODIFIER_H

#include "PImageModifierBase.h"

class PDuoToneImageModifier : public PImageModifierBase
{
public:
    PDuoToneImageModifier();
    virtual ~PDuoToneImageModifier();
    PDuoToneImageModifier(const PDuoToneImageModifier &pDuoToneImageModifier);

    virtual PImageModifierBase* clone() const override;
    virtual void transform(cv::Mat *src, cv::Mat *dst) override;
};

#endif // PDUOTONEIMAGEMODIFIER_H
