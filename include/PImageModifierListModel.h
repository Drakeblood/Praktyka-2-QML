#ifndef PIMAGEMODIFIERLISTMODEL_H
#define PIMAGEMODIFIERLISTMODEL_H

#include <QAbstractListModel>
#include <QObject>

class PImageModifierList;

class PImageModifierListModel : public QAbstractListModel
{
public:
    explicit PImageModifierListModel(QObject *parent = nullptr);

    enum {
        TextRole = Qt::UserRole,
        ModifierIndexRole
    };

    // Basic functionality:
    /*int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    virtual QHash<int, QByteArray> roleNames() const override;*/

private:
    PImageModifierList *mList;
};

#endif // PIMAGEMODIFIERLISTMODEL_H
