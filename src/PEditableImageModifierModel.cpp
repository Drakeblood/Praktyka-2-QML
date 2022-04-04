#include "include/PEditableImageModifierModel.h"
#include "include/PEditableImageModifierList.h"

PEditableImageModifierModel::PEditableImageModifierModel(QObject *parent)
    : QAbstractListModel(parent)
    , mList(nullptr)
{

}

int PEditableImageModifierModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.

    if(mList)
    {
        return mList->items().size();
    }
    return 0;
}

QVariant PEditableImageModifierModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid() && mList)
    {
        const ImageModifierOptionItem item = mList->items().at(index.row());
        switch (role)
        {
        case TextRole:
            return QVariant(item.text);
        }
    }
    return QVariant();
}

bool PEditableImageModifierModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (mList)
    {
        ImageModifierOptionItem item = mList->items().at(index.row());
        switch (role)
        {
        case TextRole:
            item.text = value.toString();
            break;
        }

        if (mList->setItemAt(index.row(), item)) {
            emit dataChanged(index, index, QVector<int>() << role);
            return true;
        }
    }
    return false;
}

Qt::ItemFlags PEditableImageModifierModel::flags(const QModelIndex &index) const
{
    if (index.isValid())
    {
        return Qt::ItemIsEditable;
    }
    return Qt::NoItemFlags;
}

QHash<int, QByteArray> PEditableImageModifierModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[TextRole] = "text";
    //names[IndexRole] = "index";
    return names;
}

PEditableImageModifierList* PEditableImageModifierModel::list() const
{
    return mList;
}

void PEditableImageModifierModel::setList(PEditableImageModifierList *list)
{
    beginResetModel();

    if (mList)
    {
        mList->disconnect(this);
    }

    mList = list;

    if (mList) {
        connect(mList, &PEditableImageModifierList::preItemAppended, this, [=]() {
            const int index = mList->items().size();
            beginInsertRows(QModelIndex(), index, index);
        });
        connect(mList, &PEditableImageModifierList::postItemAppended, this, [=]() {
            endInsertRows();
        });

        connect(mList, &PEditableImageModifierList::preItemRemoved, this, [=](int index) {
            beginRemoveRows(QModelIndex(), index, index);
        });
        connect(mList, &PEditableImageModifierList::postItemRemoved, this, [=]() {
            endRemoveRows();
        });
    }

    endResetModel();
}

void PEditableImageModifierModel::move(int from, int to)
{
        beginResetModel();
        //beginMoveRows(QModelIndex(), from, from, QModelIndex(), to);

        auto mList = list();
        if(mList)
        {
            mList->reorderItem(from, to);
        }

        //endMoveRows();
        endResetModel();
}
