#include "include/PImageTransformationList.h"
#include "include/PImageTransform.h"

PImageTransformationList::PImageTransformationList(QObject *parent)
    : QObject{parent}
{
    mItems.append({QStringLiteral("Flip Image"), 1});
    mItems.append({QStringLiteral("Noise Image"), 2});
}

QVector<ImageTranformationOptionItem> PImageTransformationList::items() const
{
    return mItems;
}

bool PImageTransformationList::setItemAt(int index, const ImageTranformationOptionItem &item)
{
    if (index < 0 || index >= mItems.size())
        return false;

    /*const ImageTranformationOptionItem &oldItem = mItems.at(index);
    if (item.name == oldItem.name && item.imageTransform == oldItem.imageTransform)
        return false;*/

    mItems[index] = item;
    return true;
}

void PImageTransformationList::doTransform(int index)
{

}
