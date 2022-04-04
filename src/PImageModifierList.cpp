#include "include/PImageModifierList.h"
#include "include/ImageModifiers/PFlipHorizontallyImageModifier.h"
#include "include/ImageModifiers/PRotateImageModifier.h"

PImageModifierList::PImageModifierList(QObject *parent)
    : QObject{parent}
{
    modifiers.append({"Flip Image Horizontally"});
    modifiers.append({"Rotate Image"});
}
