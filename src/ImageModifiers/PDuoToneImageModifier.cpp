#include "include/ImageModifiers/PDuoToneImageModifier.h"

PDuoToneImageModifier::PDuoToneImageModifier()
{
    text = "Duo-Tone";
    paramsMap.insert("Red - 0, Green - 1, Blue - 2", 2);
    paramsMap.insert("Exp", 1.4);
}

PDuoToneImageModifier::~PDuoToneImageModifier()
{
    qDebug() << "PDuoToneImageModifier destroyed.";
}

PDuoToneImageModifier::PDuoToneImageModifier(const PDuoToneImageModifier &pDuoToneImageModifier)
    : PImageModifierBase(pDuoToneImageModifier)
{

}

PImageModifierBase* PDuoToneImageModifier::clone() const
{
    return new PDuoToneImageModifier(*this);
}

cv::Mat exponential_function(cv::Mat channel, float exp)
{
    cv::Mat table(1, 256, CV_8U);

    for (int i = 0; i < 256; i++)

        table.at<uchar>(i) = cv::min((int)std::pow(i, exp), 255);

    cv::LUT(channel, table, channel);

    return channel;

}

void PDuoToneImageModifier::transform(cv::Mat *src, cv::Mat *dst)
{
    qDebug() << "Duo-Tone image modifier";

    int color = paramsMap["Red - 0, Green - 1, Blue - 2"].toInt();
    float exp = paramsMap["Exp"].toFloat();

    int s1 = 0;
    int s2 = 0;
    int s3 = 3;

    switch(color)
    {
        case 0:
        {
            s1 = 2;
            s2 = 3;
            s3 = 0;
            break;
        }
        case 1:
        {
            s1 = 1;
            s2 = 3;
            s3 = 0;
            break;
        }
        case 2:
        {
            s1 = 0;
            s2 = 0;
            s3 = 3;
            break;
        }
    }

    cv::Mat channels[3];

    split(*src, channels);

    for (int i = 0; i < 3; i++)
    {
        if ((i == s1)||(i == s2))
        {
            channels[i] = exponential_function(channels[i], exp);
        }
        else
        {
            if (s3)
            {
                channels[i] = exponential_function(channels[i], 2 - exp);
            }
            else
            {
                channels[i] = cv::Mat::zeros(channels[i].size(), CV_8UC1);
            }
        }
    }
    std::vector<cv::Mat> newChannels{channels[0], channels[1], channels[2]};
    merge(newChannels, *dst);
}
