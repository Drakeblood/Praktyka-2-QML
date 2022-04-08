#ifndef PFLIPHORIZONTALLYIMAGEMODIFIER_H
#define PFLIPHORIZONTALLYIMAGEMODIFIER_H

#include <include/ImageModifiers/PImageModifierBase.h>

class PFlipHorizontallyImageModifier : public PImageModifierBase
{
public:
    PFlipHorizontallyImageModifier();
    virtual ~PFlipHorizontallyImageModifier();
    PFlipHorizontallyImageModifier(const PFlipHorizontallyImageModifier &pRotateImageModifier);

    virtual PImageModifierBase* clone() const override;
    virtual void transform(cv::Mat *src, cv::Mat *dst) override;
};

#endif // PFLIPHORIZONTALLYIMAGEMODIFIER_H
