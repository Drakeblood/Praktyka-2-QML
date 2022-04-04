#ifndef PIMAGETRANSFORMATIONLIST_H
#define PIMAGETRANSFORMATIONLIST_H

#include <QObject>
#include <QVector>

struct ImageTranformationOptionItem
{
    QString text;
};

class PImageTransformationList : public QObject
{
    Q_OBJECT
public:
    explicit PImageTransformationList(QObject *parent = nullptr);

    QVector<ImageTranformationOptionItem> items() const;

    bool setItemAt(int index, const ImageTranformationOptionItem &item);

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
    QVector<ImageTranformationOptionItem> mItems;

};

#endif // PIMAGETRANSFORMATIONLIST_H
