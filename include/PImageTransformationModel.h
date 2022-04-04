#ifndef PIMAGETRANSFORMATIONMODEL_H
#define PIMAGETRANSFORMATIONMODEL_H

#include <QAbstractListModel>

class PImageTransformationList;

class PImageTransformationModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(PImageTransformationList *list READ list WRITE setList)

 public:
     explicit PImageTransformationModel(QObject *parent = nullptr);

     enum {
         TextRole = Qt::UserRole,
     };

     // Basic functionality:
     int rowCount(const QModelIndex &parent = QModelIndex()) const override;

     QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

     // Editable:
     bool setData(const QModelIndex &index, const QVariant &value,
                  int role = Qt::EditRole) override;

     Qt::ItemFlags flags(const QModelIndex& index) const override;

     virtual QHash<int, QByteArray> roleNames() const override;

     PImageTransformationList *list() const;
     void setList(PImageTransformationList *list);

     Q_INVOKABLE
     void move(int from, int to);

 private:
     PImageTransformationList *mList;
};

#endif // PIMAGETRANSFORMATIONMODEL_H
