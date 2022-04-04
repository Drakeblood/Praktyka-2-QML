#include "include/PImageTransformationModel.h"
#include "include/PImageTransformationList.h"

PImageTransformationModel::PImageTransformationModel(QObject *parent)
    : QAbstractListModel(parent)
    , mList(nullptr)
{

}

int PImageTransformationModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.

    if(mList)
    {
        return mList->items().size();
    }
    return 0;
}

QVariant PImageTransformationModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid() && mList)
    {
        const ImageTranformationOptionItem item = mList->items().at(index.row());
        switch (role)
        {
        case TextRole:
            return QVariant(item.text);
        }
    }
    return QVariant();
}

bool PImageTransformationModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (mList)
    {
        ImageTranformationOptionItem item = mList->items().at(index.row());
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

Qt::ItemFlags PImageTransformationModel::flags(const QModelIndex &index) const
{
    if (index.isValid())
    {
        return Qt::ItemIsEditable;
    }
    return Qt::NoItemFlags;
}

QHash<int, QByteArray> PImageTransformationModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[TextRole] = "text";
    //names[IndexRole] = "index";
    return names;
}

PImageTransformationList* PImageTransformationModel::list() const
{
    return mList;
}

void PImageTransformationModel::setList(PImageTransformationList *list)
{
    beginResetModel();

    if (mList)
    {
        mList->disconnect(this);
    }

    mList = list;

    if (mList) {
        connect(mList, &PImageTransformationList::preItemAppended, this, [=]() {
            const int index = mList->items().size();
            beginInsertRows(QModelIndex(), index, index);
        });
        connect(mList, &PImageTransformationList::postItemAppended, this, [=]() {
            endInsertRows();
        });

        connect(mList, &PImageTransformationList::preItemRemoved, this, [=](int index) {
            beginRemoveRows(QModelIndex(), index, index);
        });
        connect(mList, &PImageTransformationList::postItemRemoved, this, [=]() {
            endRemoveRows();
        });
    }

    endResetModel();
}

void PImageTransformationModel::move(int from, int to)
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
