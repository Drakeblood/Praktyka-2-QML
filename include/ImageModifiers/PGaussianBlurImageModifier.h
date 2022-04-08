#ifndef PGAUSSIANBLURIMAGEMODIFIER_H
#define PGAUSSIANBLURIMAGEMODIFIER_H

#include "include/ImageModifiers/PImageModifierBase.h"

class PGaussianBlurImageModifier : public PImageModifierBase
{
public:
    PGaussianBlurImageModifier();
    virtual ~PGaussianBlurImageModifier();
    PGaussianBlurImageModifier(const PGaussianBlurImageModifier &pRotateImageModifier);

    virtual PImageModifierBase* clone() const override;
    virtual void transform(cv::Mat *src, cv::Mat *dst) override;
};

#endif // PGAUSSIANBLURIMAGEMODIFIER_H
