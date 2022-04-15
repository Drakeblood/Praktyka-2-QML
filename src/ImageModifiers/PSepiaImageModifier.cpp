#include "include/ImageModifiers/PSepiaImageModifier.h"

PSepiaImageModifier::PSepiaImageModifier()
{
    text = "Sepia";
}

PSepiaImageModifier::~PSepiaImageModifier()
{
    qDebug() << "PSepiaImageModifier destroyed.";
}

PSepiaImageModifier::PSepiaImageModifier(const PSepiaImageModifier &pSepiaImageModifier)
    : PImageModifierBase(pSepiaImageModifier)
{

}

PImageModifierBase* PSepiaImageModifier::clone() const
{
    return new PSepiaImageModifier(*this);
}

void PSepiaImageModifier::transform(cv::Mat *src, cv::Mat *dst)
{
    qDebug() << "Sepia image modifier";

    cvtColor(*dst, *dst, cv::COLOR_BGR2RGB);
    cv::transform(*dst, *dst, cv::Matx33f(0.393,0.769,0.189,
                                          0.349,0.686,0.168,
                                          0.272,0.534,0.131));
    cvtColor(*dst, *dst, cv::COLOR_RGB2BGR);
}
