#include "include/ImageModifiers/PImageModifierBase.h"
#include "include/PEditableImageModifierListModel.h"
#include "include/PEditableImageModifierList.h"

#include "QDebug"

PEditableImageModifierListModel::PEditableImageModifierListModel(QObject *parent)
    : QAbstractListModel(parent)
    , mList(nullptr)
{

}

PEditableImageModifierListModel::~PEditableImageModifierListModel()
{
    qDebug() << "PEditableImageModifierListModel destroyed.";
}

int PEditableImageModifierListModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.

    if(mList)
    {
        return mList->items().size();
    }
    return 0;
}

QVariant PEditableImageModifierListModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid() && mList)
    {
        const PImageModifierBase *item = mList->items().at(index.row());
        switch (role)
        {
        case TextRole:
            return QVariant(item->getText());
        }
    }
    return QVariant();
}

bool PEditableImageModifierListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (mList)
    {
        PImageModifierBase *item = mList->items().at(index.row());
        switch (role)
        {

        }

        if (mList->setModifierAt(index.row(), item)) {
            emit dataChanged(index, index, QVector<int>() << role);
            return true;
        }
    }
    return false;
}

Qt::ItemFlags PEditableImageModifierListModel::flags(const QModelIndex &index) const
{
    if (index.isValid())
    {
        return Qt::ItemIsEditable;
    }
    return Qt::NoItemFlags;
}

QHash<int, QByteArray> PEditableImageModifierListModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[TextRole] = "text";
    //names[IndexRole] = "index";
    return names;
}

PEditableImageModifierList* PEditableImageModifierListModel::list() const
{
    return mList;
}

void PEditableImageModifierListModel::setList(PEditableImageModifierList *list)
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

void PEditableImageModifierListModel::move(int from, int to)
{
        beginResetModel();
        //beginMoveRows(QModelIndex(), from, from, QModelIndex(), to);

        auto mList = list();
        if(mList)
        {
            mList->reorderModifiers(from, to);
        }

        //endMoveRows();
        endResetModel();
}
