#include "include/ImageModifiers/PFlipHorizontallyImageModifier.h"


PFlipHorizontallyImageModifier::PFlipHorizontallyImageModifier()
{
    text = "Flip Horizontally";
}

PFlipHorizontallyImageModifier::~PFlipHorizontallyImageModifier()
{
    qDebug() << "PFlipHorizontallyImageModifier destroyed.";
}

PFlipHorizontallyImageModifier::PFlipHorizontallyImageModifier(const PFlipHorizontallyImageModifier &pFlipHorizontallyImageModifier)
    : PImageModifierBase(pFlipHorizontallyImageModifier)
{

}

PImageModifierBase* PFlipHorizontallyImageModifier::clone() const
{
    return new PFlipHorizontallyImageModifier(*this);
}

void PFlipHorizontallyImageModifier::transform(cv::Mat *src, cv::Mat *dst)
{
    qDebug() << "Flip image modifier";

    cv::flip(*src, *dst, 1);
}
