#ifndef PIMAGEMODIFIERLIST_H
#define PIMAGEMODIFIERLIST_H

#include <QObject>

class PImageModifierBase;

/** Class that store image modifier options */
class PImageModifierList : public QObject
{
    Q_OBJECT

public:
    QVector<PImageModifierBase*> modifiers;

public:
    explicit PImageModifierList(QObject *parent = nullptr);
    virtual ~PImageModifierList();
};

#endif // PIMAGEMODIFIERLIST_H
