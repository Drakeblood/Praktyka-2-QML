#ifndef PEDITABLEIMAGEMODIFIERLIST_H
#define PEDITABLEIMAGEMODIFIERLIST_H

#include <QObject>
#include <QVector>

struct ImageModifierOptionItem
{
    QString text;
    int modifierIndex;
};

class PEditableImageModifierList : public QObject
{
    Q_OBJECT
public:
    explicit PEditableImageModifierList(QObject *parent = nullptr);

    QVector<ImageModifierOptionItem> items() const;

    bool setItemAt(int index, const ImageModifierOptionItem &item);

    void reorderItem(int from, int to);

signals:
    void preItemAppended();
    void postItemAppended();

    void preItemRemoved(int index);
    void postItemRemoved();

public slots:
    void doTransform(int index);
    void appendItem();

private:
    QVector<ImageModifierOptionItem> mItems;

};

#endif // PEDITABLEIMAGEMODIFIERLIST_H
