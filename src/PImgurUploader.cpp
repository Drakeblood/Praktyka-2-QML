#include "include/PImgurUploader.h"

#include <QNetworkAccessManager>
#include <QDebug>
#include <QBuffer>
#include <QUrlQuery>
#include <QImage>
#include <QNetworkReply>
#include <QDomDocument>

PImgurUploader::PImgurUploader(QObject * parent)
    : QObject(parent)
    , clientID("f96428a3356ca93")
    , m_uploadedImageUrl("link")
{
    m_manager = new QNetworkAccessManager(this);

    connect(m_manager, SIGNAL(finished(QNetworkReply *)),
            this, SLOT(requestFinished(QNetworkReply *)));
}

bool PImgurUploader::upload(QString title, QString description)
{
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    imageToUpload->save(&buffer, "PNG");

    QUrlQuery urlQuery;
    urlQuery.addQueryItem("title", title);
    urlQuery.addQueryItem("description", description);

    QNetworkRequest request;
    QUrl url("https://api.imgur.com/3/image");
    url.setQuery(urlQuery);
    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,
                      "application/application/x-www-form-urlencoded");
    request.setRawHeader("Authorization", "Client-ID f96428a3356ca93");

    m_manager->post(request, byteArray);

    return true;
}

void PImgurUploader::requestFinished(QNetworkReply *reply)
{
    qDebug() << "Request Finished.";

    if (reply->error() != QNetworkReply::NoError)
    {
        qDebug() << "Network error: " << reply->error();

        reply->deleteLater();
        return;
    }

    std::string str = reply->readAll().toStdString();
    std::string chars = "\\";

    size_t pos = str.rfind("link");
    if (pos != std::string::npos)
    {
        std::string strE = str.substr(pos);
        strE.erase(remove_if(strE.begin(), strE.end(),
                             [&chars](const char& c) {
            return chars.find(c) != std::string::npos;
        }),
                   strE.end());

        pos = strE.find("http");
        if (pos != std::string::npos)
        {
            strE = strE.substr(pos);
            pos = strE.find("\"}");
            if (pos != std::string::npos)
            {
                strE = strE.substr(0, pos);
                setUploadedImageUrl(strE.c_str());
                qDebug() << strE.c_str();
            }
        }
    }
    reply->deleteLater();
}

QString PImgurUploader::uploadedImageUrl() const
{
    return m_uploadedImageUrl;
}

void PImgurUploader::setUploadedImageUrl(const QString &newUploadedImageUrl)
{
    if(m_uploadedImageUrl != newUploadedImageUrl)
    {
        m_uploadedImageUrl = newUploadedImageUrl;
    }
    emit uploadedImageUrlChanged();
}
