#ifndef FILEDOWNLOADER_H
#define FILEDOWNLOADER_H

#include <QObject>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

class FileDownloader : public QObject
{
    Q_OBJECT
public:
    explicit FileDownloader(QUrl imageUrl, QObject *parent = 0);

    virtual ~FileDownloader();

    QByteArray downloadedData() const;

signals:
        void downloaded();
        void update(qint64, qint64);

private slots:

    void fileDownloaded(QNetworkReply* pReply);
    void updateDownloadProgress(qint64, qint64);

private:

    QNetworkAccessManager m_WebCtrl;
    QNetworkReply *reply;
    QByteArray m_DownloadedData;
    qint64 fileSize;
    bool httpRequestAborted;

};

#endif // FILEDOWNLOADER_H
