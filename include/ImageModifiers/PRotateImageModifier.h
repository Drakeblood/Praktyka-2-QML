#ifndef PROTATEIMAGEMODIFIER_H
#define PROTATEIMAGEMODIFIER_H

#include "include/ImageModifiers/PImageModifierBase.h"

class PRotateImageModifier : public PImageModifierBase
{
public:
    PRotateImageModifier();
    virtual ~PRotateImageModifier();
    PRotateImageModifier(const PRotateImageModifier &pRotateImageModifier);

    virtual PImageModifierBase* clone() const override;
    virtual void transform(cv::Mat *src, cv::Mat *dst) override;
};

#endif // PROTATEIMAGEMODIFIER_H
