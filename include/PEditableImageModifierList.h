#ifndef PEDITABLEIMAGEMODIFIERLIST_H
#define PEDITABLEIMAGEMODIFIERLIST_H

#include "include/PImageModifierList.h"

#include <QObject>
#include <QVector>

class PImageModifierBase;

/** Class that store chosen image modifier options */
class PEditableImageModifierList : public QObject
{
    Q_OBJECT

public:
    QVector<PImageModifierBase*> mChosenModifiers;

private:
    static PImageModifierList modifierList;

public:
    explicit PEditableImageModifierList(QObject *parent = nullptr);
    virtual ~PEditableImageModifierList();

    QVector<PImageModifierBase*> items() const;

    bool setModifierAt(int index, PImageModifierBase *modifier);
    void reorderModifiers(int from, int to);
    void appendModifier(const PImageModifierBase *imageModifier);

signals:
    void preItemAppended();
    void postItemAppended();

    void preItemRemoved(int index);
    void postItemRemoved();

    void listItemChanged();

public slots:
    void appendModifier(int modifierIndex);
    void removeModifier(int modifierIndex);
    void cloneModifier(int modifierIndex);

    QStringList getModifierParamNames(int modifierIndex);
    QList<QVariant> getModifierParams(int modifierIndex);

    void setModifierParams(int modifierIndex);

};

#endif // PEDITABLEIMAGEMODIFIERLIST_H
