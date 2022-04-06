#ifndef PEDITABLEIMAGEMODIFIERMODEL_H
#define PEDITABLEIMAGEMODIFIERMODEL_H

#include <QAbstractListModel>

class PEditableImageModifierList;

class PEditableImageModifierListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(PEditableImageModifierList *list READ list WRITE setList)

private:
    PEditableImageModifierList *mList;

public:
    enum {
        TextRole = Qt::UserRole,
        ModifierIndexRole
    };

public:
    explicit PEditableImageModifierListModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    PEditableImageModifierList *list() const;
    void setList(PEditableImageModifierList *list);

    Q_INVOKABLE
    void move(int from, int to);

};

#endif // PEDITABLEIMAGEMODIFIERMODEL_H
