#ifndef PFLIPHORIZONTALLYIMAGEMODIFIER_H
#define PFLIPHORIZONTALLYIMAGEMODIFIER_H

#include <include/ImageModifiers/PImageModifierBase.h>

class PFlipHorizontallyImageModifier : public PImageModifierBase
{
public:
    PFlipHorizontallyImageModifier();

    virtual void transform(cv::Mat *src, cv::Mat *dst, QStringList stringParams) override;
};

#endif // PFLIPHORIZONTALLYIMAGEMODIFIER_H
