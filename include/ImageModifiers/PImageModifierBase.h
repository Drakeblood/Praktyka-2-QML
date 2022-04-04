#ifndef PIMAGEMODIFIERBASE_H
#define PIMAGEMODIFIERBASE_H

#include <QVariant>
#include <QStringList>

class PImageModifierBase
{
protected:
    QStringList paramNames;

public:
    PImageModifierBase();

    virtual void transform(QVariant args...) = 0;

    const QStringList& getParamNames() const;
};

#endif // PIMAGEMODIFIERBASE_H
