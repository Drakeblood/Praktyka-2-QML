#ifndef PPIXELATEIMAGEMODIFIER_H
#define PPIXELATEIMAGEMODIFIER_H

#include "include/ImageModifiers/PImageModifierBase.h"

class PPixelateImageModifier : public PImageModifierBase
{
public:
    PPixelateImageModifier();
    virtual ~PPixelateImageModifier();
    PPixelateImageModifier(const PPixelateImageModifier &pPixelateImageModifier);

    virtual PImageModifierBase* clone() const override;
    virtual void transform(cv::Mat *src, cv::Mat *dst) override;
};

#endif // PPIXELATEIMAGEMODIFIER_H
