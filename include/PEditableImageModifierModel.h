#ifndef PEDITABLEIMAGEMODIFIERMODEL_H
#define PEDITABLEIMAGEMODIFIERMODEL_H

#include <QAbstractListModel>

class PEditableImageModifierList;

class PEditableImageModifierModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(PEditableImageModifierList *list READ list WRITE setList)

 public:
     explicit PEditableImageModifierModel(QObject *parent = nullptr);

     enum {
         TextRole = Qt::UserRole,
         ModifierIndexRole
     };

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

 private:
     PEditableImageModifierList *mList;
};

#endif // PEDITABLEIMAGEMODIFIERMODEL_H
