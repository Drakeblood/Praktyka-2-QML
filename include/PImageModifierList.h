#ifndef PIMAGEMODIFIERLIST_H
#define PIMAGEMODIFIERLIST_H

#include <QObject>

#include "include/PEditableImageModifierList.h"

class PImageModifierList : public QObject
{
    Q_OBJECT
public:
    explicit PImageModifierList(QObject *parent = nullptr);

private:
    QVector<ImageModifierOptionItem> modifiers;
};

#endif // PIMAGEMODIFIERLIST_H
