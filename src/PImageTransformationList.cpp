#include "include/PImageTransformationList.h"
#include "include/ImageTransforms/PImageTransformBase.h"

#include "QDebug"

PImageTransformationList::PImageTransformationList(QObject *parent)
    : QObject{parent}
{
    mItems.append({QStringLiteral("Flip Image")});
    mItems.append({QStringLiteral("Noise Image")});
}

QVector<ImageTranformationOptionItem> PImageTransformationList::items() const
{
    return mItems;
}

bool PImageTransformationList::setItemAt(int index, const ImageTranformationOptionItem &item)
{
    if (index < 0 || index >= mItems.size())
        return false;

    const ImageTranformationOptionItem &oldItem = mItems.at(index);
    if (item.text == oldItem.text)
        return false;

    mItems[index] = item;
    return true;
}

void PImageTransformationList::reorderItem(int from, int to)
{
    mItems.move(from, to);
}

void PImageTransformationList::doTransform(int index)
{

}

void PImageTransformationList::appendItem()
{
    emit preItemAppended();

    mItems.append({QStringLiteral("Test Image")});

    emit postItemAppended();
}
