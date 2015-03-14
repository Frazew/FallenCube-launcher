#ifndef FILEDOWNLOADER_H
#define FILEDOWNLOADER_H

#include <QObject>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QFile>

class FileDownloader : public QObject
{
    Q_OBJECT
public:
    explicit FileDownloader(QUrl imageUrl, QFile *file, bool compress, QObject *parent = 0);

    virtual ~FileDownloader();

    QByteArray downloadedData() const;

signals:
        void downloaded();
        void update(qint64, qint64);

private slots:

    void fileDownloaded(QNetworkReply* pReply);
    void updateDownloadProgress(qint64, qint64);
    void httpReadyRead();

private:

    QNetworkAccessManager m_WebCtrl;
    QNetworkReply *reply;
    QByteArray m_DownloadedData;
    qint64 fileSize;
    QFile *destFile;
    bool httpRequestAborted;
    bool shouldUncompress;

};

#endif // FILEDOWNLOADER_H
