#ifndef PIMAGEMODIFIEREXECUTER_H
#define PIMAGEMODIFIEREXECUTER_H

#include "include/PEditableImageModifierList.h"

#include <QObject>
#include "QtConcurrent/QtConcurrent"
#include "QThread"

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"

class PImageStreamer;
class PImageModifierBase;

/** Class that modify images*/
class PImageModifierExecutor : public QThread
{
    Q_OBJECT

private:
    QVector<PImageModifierBase*>* imageModifierOptionItems;
    PImageStreamer* imageStreamer;

    QVector<QFutureWatcher<void>*> futureWatchers;

    int executeCounter;

public:
    explicit PImageModifierExecutor(QObject *parent = nullptr);
    virtual ~PImageModifierExecutor();

    void setupExecutor(QVector<PImageModifierBase*>* _imageModifierOptionItems, PImageStreamer* _imageStreamer);

    Q_INVOKABLE
    void executeModifiers();

protected:
    void run();

private:
    void executeModifiers(int index);

};

#endif // PIMAGEMODIFIEREXECUTER_H
