#include "include/PImageModifierList.h"
#include "include/ImageModifiers/PFlipHorizontallyImageModifier.h"
#include "include/ImageModifiers/PRotateImageModifier.h"
#include "include/ImageModifiers/PGaussianBlurImageModifier.h"

#include "QDebug"

PImageModifierList::PImageModifierList(QObject *parent)
    : QObject{parent}
    , modifiers(
        {new PFlipHorizontallyImageModifier,
         new PRotateImageModifier,
         new PGaussianBlurImageModifier
        })
{

}

PImageModifierList::~PImageModifierList()
{
    qDebug() << "PImageModifierList destroyed.";
}
