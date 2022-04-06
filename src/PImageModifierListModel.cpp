#include "include/PImageModifierListModel.h"
#include "include/PImageModifierList.h"

PImageModifierListModel::PImageModifierListModel(QObject *parent)
    : QAbstractListModel{parent}
    , mList(nullptr)
{

}
