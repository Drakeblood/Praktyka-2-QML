#ifndef PGAUSSIANNOISEIMAGEMODIFIER_H
#define PGAUSSIANNOISEIMAGEMODIFIER_H

#include "include/ImageModifiers/PImageModifierBase.h"

class PGaussianNoiseImageModifier : public PImageModifierBase
{
public:
    PGaussianNoiseImageModifier();
    virtual ~PGaussianNoiseImageModifier();
    PGaussianNoiseImageModifier(const PGaussianNoiseImageModifier &pGaussianNoiseImageModifier);

    virtual PImageModifierBase* clone() const override;
    virtual void transform(cv::Mat *src, cv::Mat *dst) override;
};

#endif // PGAUSSIANNOISEIMAGEMODIFIER_H
