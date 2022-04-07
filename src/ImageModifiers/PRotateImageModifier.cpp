#include "include/ImageModifiers/PRotateImageModifier.h"

PRotateImageModifier::PRotateImageModifier()
{
    paramNames.append({"Degree min", "Degree max"});
}

void PRotateImageModifier::transform(cv::Mat *src, cv::Mat *dst, QStringList stringParams)
{
    qDebug() << "Rotate image modifier";

    double degree = 20;

    cv::Point2f centerPoint((src->cols-1)/2.0, (src->rows-1)/2.0);
    cv::Mat rot = cv::getRotationMatrix2D(centerPoint, degree, 1.0);

    cv::Rect2f bbox = cv::RotatedRect(cv::Point2f(), src->size(), degree).boundingRect2f();

    rot.at<double>(0,2) += bbox.width/2.0 - src->cols/2.0;
    rot.at<double>(1,2) += bbox.height/2.0 - src->rows/2.0;

    cv::warpAffine(*src, *dst, rot, bbox.size());
}
