#include "include/PImageModifierList.h"
#include "include/ImageModifiers/PFlipHorizontallyImageModifier.h"
#include "include/ImageModifiers/PRotateImageModifier.h"

PImageModifierList::PImageModifierList(QObject *parent)
    : QObject{parent}
    , modifiers(
        {new PFlipHorizontallyImageModifier,
         new PRotateImageModifier
        })
{

}
