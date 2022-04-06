#include "include/PImageModifierList.h"
#include "include/ImageModifiers/PFlipHorizontallyImageModifier.h"
#include "include/ImageModifiers/PRotateImageModifier.h"

#include "QDebug"

PImageModifierList::PImageModifierList(QObject *parent)
    : QObject{parent}
    , modifiers(
        {new PFlipHorizontallyImageModifier,
         new PRotateImageModifier
        })
{

}

PImageModifierList::~PImageModifierList()
{
    qDebug() << "PImageModifierList destroyed.";
}
