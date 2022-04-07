#ifndef PIMAGEMODIFIEREXECUTER_H
#define PIMAGEMODIFIEREXECUTER_H

#include <QObject>
#include "QtConcurrent/QtConcurrent"
#include "QThread"

#include "include/PEditableImageModifierList.h"

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"

class PImageStreamer;

/** Class that modify images*/
class PImageModifierExecutor : public QThread
{
    Q_OBJECT

private:
    QVector<ImageModifierOptionItem>* imageModifierOptionItems;
    QVector<PImageModifierBase*>* modifierList;
    PImageStreamer* imageStreamer;

    QVector<QFutureWatcher<void>*> futureWatchers;

    int executeCounter;

public:
    explicit PImageModifierExecutor(QObject *parent = nullptr);
    virtual ~PImageModifierExecutor();

    void setupExecutor(QVector<ImageModifierOptionItem>* _imageModifierOptionItems, QVector<PImageModifierBase*>* _modifierList, PImageStreamer* _imageStreamer);

    Q_INVOKABLE
    void executeModifiers();

protected:
    void run();

private:
    void executeModifiers(int index);

};

#endif // PIMAGEMODIFIEREXECUTER_H
