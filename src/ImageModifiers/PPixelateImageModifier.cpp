#include "include/ImageModifiers/PPixelateImageModifier.h"

PPixelateImageModifier::PPixelateImageModifier()
{
    text = "Pixelate Image";
    paramsMap.insert("Min", 10);
    paramsMap.insert("Max", 20);
}

PPixelateImageModifier::~PPixelateImageModifier()
{
    qDebug() << "PPixelateImageModifier destroyed.";
}

PPixelateImageModifier::PPixelateImageModifier(const PPixelateImageModifier &pPixelateImageModifier)
    : PImageModifierBase(pPixelateImageModifier)
{

}

PImageModifierBase* PPixelateImageModifier::clone() const
{
    return new PPixelateImageModifier(*this);
}

void PPixelateImageModifier::transform(cv::Mat *src, cv::Mat *dst)
{
    qDebug() << "Pixelate image modifier";

    int size = fRand(paramsMap["Min"].toInt(), paramsMap["Max"].toInt());
    if(!isOdd(size))
    {
        size++;//only odd
    }

    int max_step = (size - 1) / 2;
    for (int i = max_step; i < dst->rows - max_step; i += size)
    {
        for (int j = max_step; j < dst->cols - max_step; j += size)
        {
            cv::Vec3b colour = dst->at<cv::Vec3b>(cv::Point(j, i));
            for (int k = -max_step; k <= max_step; k++)
            {
                for (int l = -max_step; l <= max_step; l++)
                {
                    dst->at<cv::Vec3b>(cv::Point(j - k, i - l)) = colour;
                }
            }
        }
    }
}
