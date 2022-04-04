#ifndef PIMAGETRANSFORMBASE_H
#define PIMAGETRANSFORMBASE_H

#include <QVariant>
#include <QStringList>

class PImageTransformBase
{
protected:
    QStringList paramNames;

public:
    PImageTransformBase();

    virtual void transform(QVariant args...) = 0;

    const QStringList& getParamNames() const;
};

#endif // PIMAGETRANSFORMBASE_H
