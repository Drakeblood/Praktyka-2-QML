#ifndef PEDITABLEIMAGEMODIFIERLIST_H
#define PEDITABLEIMAGEMODIFIERLIST_H

#include <QObject>
#include <QVector>

class PImageModifierBase;

struct ImageModifierOptionItem
{
    QString text;
    int modifierIndex;
};

/** Class that store chosen image modifier options */
class PEditableImageModifierList : public QObject
{
    Q_OBJECT

public:
    QVector<ImageModifierOptionItem> mItems;

public:
    explicit PEditableImageModifierList(QObject *parent = nullptr);
    virtual ~PEditableImageModifierList();

    QVector<ImageModifierOptionItem> items() const;

    bool setItemAt(int index, const ImageModifierOptionItem &item);

    void reorderItem(int from, int to);

signals:
    void preItemAppended();
    void postItemAppended();

    void preItemRemoved(int index);
    void postItemRemoved();

public slots:
    void doTransform();
    void appendItem(QString _text, int _modifierIndex);

};

#endif // PEDITABLEIMAGEMODIFIERLIST_H
