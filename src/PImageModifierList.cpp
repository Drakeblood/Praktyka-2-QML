#include "include/PImageModifierList.h"
#include "include/ImageModifiers/PFlipHorizontallyImageModifier.h"
#include "include/ImageModifiers/PRotateImageModifier.h"
#include "include/ImageModifiers/PGaussianBlurImageModifier.h"
#include "include/ImageModifiers/PContrastImageModifier.h"
#include "include/ImageModifiers/PBrightnessImageModifier.h"

#include "QDebug"

PImageModifierList::PImageModifierList(QObject *parent)
    : QObject{parent}
    , modifiers(
        {new PFlipHorizontallyImageModifier,
         new PRotateImageModifier,
         new PGaussianBlurImageModifier,
         new PContrastImageModifier,
         new PBrightnessImageModifier
        })
{

}

PImageModifierList::~PImageModifierList()
{
    for(int i = 0; i < modifiers.size(); i++)
    {
        delete modifiers[i];
    }
    qDebug() << "PImageModifierList destroyed.";
}

PImageModifierBase* PImageModifierList::operator[](const int &index) const
{
    return modifiers[index];
}
