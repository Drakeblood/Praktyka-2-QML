#include "include/PEditableImageModifierList.h"
#include "include/ImageModifiers/PFlipHorizontallyImageModifier.h"
#include "include/ImageModifiers/PRotateImageModifier.h"

#include "QDebug"

PImageModifierList PEditableImageModifierList::modifierList;

PEditableImageModifierList::PEditableImageModifierList(QObject *parent)
    : QObject{parent}
{

}

PEditableImageModifierList::~PEditableImageModifierList()
{
    qDebug() << "PEditableImageModifierList destroyed.";
}

QVector<PImageModifierBase*> PEditableImageModifierList::items() const
{
    return mChosenModifiers;
}

bool PEditableImageModifierList::setModifierAt(int index, PImageModifierBase *item)
{
    if (index < 0 || index >= mChosenModifiers.size())
        return false;

    const PImageModifierBase *oldItem = mChosenModifiers.at(index);
    if (item->getText() == oldItem->getText())
        return false;

    mChosenModifiers[index] = item;
    return true;
}

void PEditableImageModifierList::reorderModifiers(int from, int to)
{
    mChosenModifiers.move(from, to);
    emit listItemChanged();
}

void PEditableImageModifierList::appendModifier(const PImageModifierBase *imageModifier)
{
    emit preItemAppended();

    mChosenModifiers.append(imageModifier->clone());
    mChosenModifiers.last()->setParent(this);

    emit postItemAppended();
    emit listItemChanged();
}

void PEditableImageModifierList::appendModifier(int modifierIndex)
{
    emit preItemAppended();

    mChosenModifiers.append({modifierList[modifierIndex]->clone()});
    mChosenModifiers.last()->setParent(this);

    emit postItemAppended();
    emit listItemChanged();
}

void PEditableImageModifierList::removeModifier(int itemIndex)
{
    if(itemIndex >= 0 && itemIndex < mChosenModifiers.size())
    {
        emit preItemRemoved(itemIndex);

        delete mChosenModifiers[itemIndex];
        mChosenModifiers.removeAt(itemIndex);

        emit postItemRemoved();
        emit listItemChanged();
    }
}

void PEditableImageModifierList::cloneModifier(int itemIndex)
{
    if(itemIndex >= 0 && itemIndex < mChosenModifiers.size())
    {
        auto *itemToClone = mChosenModifiers[itemIndex];

        appendModifier(itemToClone);
    }
}

QStringList PEditableImageModifierList::getModifierParamNames(int modifierIndex)
{
    if(modifierIndex >= 0 && modifierIndex < mChosenModifiers.size())
    {
        qDebug() << "getModifierParamNames - Modifier index: " << modifierIndex;
        return QStringList(mChosenModifiers[modifierIndex]->getParamsMap()->keys());
    }
    return QStringList();
}

QList<QVariant> PEditableImageModifierList::getModifierParams(int modifierIndex)
{
    if(modifierIndex >= 0 && modifierIndex < mChosenModifiers.size())
    {
        qDebug() << "getModifierParams - Modifier index: " << modifierIndex;
        return mChosenModifiers[modifierIndex]->getParamsMap()->values();
    }
    return QList<QVariant>();
}

void PEditableImageModifierList::setModifierParams(int modifierIndex, QList<QVariant> paramValue)
{
    qDebug() << "setModifierParams";
    auto modifierKeys = mChosenModifiers[modifierIndex]->getParamsMap()->keys();
    for(int i = 0; i < modifierKeys.length(); i++)
    {
        qDebug() << paramValue[i];
        mChosenModifiers[modifierIndex]->setParameter(modifierKeys[i], paramValue[i]);
    }
}
