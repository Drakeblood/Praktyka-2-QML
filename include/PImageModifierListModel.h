#ifndef PIMAGEMODIFIERLISTMODEL_H
#define PIMAGEMODIFIERLISTMODEL_H

#include <QAbstractListModel>
#include <QObject>

class PImageModifierListModel : public QAbstractListModel
{
public:
    explicit PImageModifierListModel(QObject *parent = nullptr);
};

#endif // PIMAGEMODIFIERLISTMODEL_H
