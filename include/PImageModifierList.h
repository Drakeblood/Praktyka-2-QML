#ifndef PIMAGEMODIFIERLIST_H
#define PIMAGEMODIFIERLIST_H

#include <QObject>

class PImageModifierBase;

/** Class that store image modifier options */
class PImageModifierList : public QObject
{
    Q_OBJECT

private:
    QVector<PImageModifierBase*> modifiers;

public:
    explicit PImageModifierList(QObject *parent = nullptr);
    virtual ~PImageModifierList();

    PImageModifierBase* operator[](const int &index) const;
};

#endif // PIMAGEMODIFIERLIST_H
