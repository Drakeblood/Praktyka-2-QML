#ifndef PIMGURUPLOADER_H
#define PIMGURUPLOADER_H

#include <QObject>
#include <QHash>

class QNetworkAccessManager;
class QNetworkReply;

class PImgurUploader : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString uploadedImageUrl READ uploadedImageUrl WRITE setUploadedImageUrl NOTIFY uploadedImageUrlChanged)

public:
    QImage *imageToUpload;

private:
    QNetworkAccessManager * m_manager;
    QString clientID;
    QString m_uploadedImageUrl;

public:
    explicit PImgurUploader(QObject *parent = nullptr);

signals:
    void uploadedImageUrlChanged();

public slots:
    bool upload(QString title, QString description);

private slots:
    void requestFinished(QNetworkReply *reply);

private:
    QString uploadedImageUrl() const;
    void setUploadedImageUrl(const QString &newUploadedImageUrl);

};

#endif // PIMGURUPLOADER_H
