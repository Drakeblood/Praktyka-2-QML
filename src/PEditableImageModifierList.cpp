#include "include/PEditableImageModifierList.h"
#include "include/ImageModifiers/PFlipHorizontallyImageModifier.h"
#include "include/ImageModifiers/PRotateImageModifier.h"

#include "QDebug"

PEditableImageModifierList::PEditableImageModifierList(QObject *parent)
    : QObject{parent}
{

}

PEditableImageModifierList::~PEditableImageModifierList()
{
    qDebug() << "PEditableImageModifierList destroyed.";
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
    emit listItemChanged();
}

void PEditableImageModifierList::appendItem(QString _text, int _modifierIndex)
{
    emit preItemAppended();

    mItems.append({_text, _modifierIndex});

    emit postItemAppended();
    emit listItemChanged();
}

void PEditableImageModifierList::removeItem(int itemIndex)
{
    emit preItemRemoved(itemIndex);

    mItems.removeAt(itemIndex);

    emit postItemRemoved();
    emit listItemChanged();
}

void PEditableImageModifierList::cloneItem(int itemIndex)
{
    auto &itemToClone = mItems[itemIndex];

    appendItem(itemToClone.text, itemToClone.modifierIndex);
}
