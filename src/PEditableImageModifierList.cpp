#include "include/PEditableImageModifierList.h"
#include "include/ImageModifiers/PImageModifierBase.h"

#include "QDebug"

PEditableImageModifierList::PEditableImageModifierList(QObject *parent)
    : QObject{parent}
{
    mItems.append({QStringLiteral("Flip Image")});
    mItems.append({QStringLiteral("Noise Image")});
}

QVector<ImageModifierOptionItem> PEditableImageModifierList::items() const
{
    return mItems;
}

bool PEditableImageModifierList::setItemAt(int index, const ImageModifierOptionItem &item)
{
    if (index < 0 || index >= mItems.size())
        return false;

    const ImageModifierOptionItem &oldItem = mItems.at(index);
    if (item.text == oldItem.text)
        return false;

    mItems[index] = item;
    return true;
}

void PEditableImageModifierList::reorderItem(int from, int to)
{
    mItems.move(from, to);
}

void PEditableImageModifierList::doTransform(int index)
{

}

void PEditableImageModifierList::appendItem()
{
    emit preItemAppended();

    mItems.append({QStringLiteral("Test Image")});

    emit postItemAppended();
}
