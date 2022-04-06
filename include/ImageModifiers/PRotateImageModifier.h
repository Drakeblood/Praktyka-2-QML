#ifndef PROTATEIMAGEMODIFIER_H
#define PROTATEIMAGEMODIFIER_H

#include "include/ImageModifiers/PImageModifierBase.h"

class PRotateImageModifier : public PImageModifierBase
{
public:
    PRotateImageModifier();

    virtual void transform(cv::Mat *src, cv::Mat *dst, QStringList stringParams) override;
};

#endif // PROTATEIMAGEMODIFIER_H
