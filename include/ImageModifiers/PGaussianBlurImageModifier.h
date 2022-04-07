#ifndef PGAUSSIANBLURIMAGEMODIFIER_H
#define PGAUSSIANBLURIMAGEMODIFIER_H

#include "include/ImageModifiers/PImageModifierBase.h"

class PGaussianBlurImageModifier : public PImageModifierBase
{
public:
    PGaussianBlurImageModifier();

    virtual void transform(cv::Mat *src, cv::Mat *dst, QStringList stringParams) override;
};

#endif // PGAUSSIANBLURIMAGEMODIFIER_H
