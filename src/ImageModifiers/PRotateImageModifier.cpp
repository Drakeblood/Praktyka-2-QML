#include "include/ImageModifiers/PRotateImageModifier.h"
#include "QDebug"

PRotateImageModifier::PRotateImageModifier()
{
    paramNames.append({"Degree min", "Degree max"});
}

void PRotateImageModifier::transform(cv::Mat *src, cv::Mat *dst, QStringList stringParams)
{
    qDebug() << "rotate";

    cv::Point2f center((src->cols - 1) / 2.0, (src->rows - 1) / 2.0);
    *dst = getRotationMatrix2D(center, 20.f, 1.0);
    //cv::rotate(*src, *dst, 20);
}
