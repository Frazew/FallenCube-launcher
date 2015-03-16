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
    FileDownloader(QUrl imageUrl, QString file, bool compress, QObject *parent = 0);
    QByteArray downloadedData() const;

signals:
        void downloaded();
        void update(qint64, qint64);

private slots:

    void fileDownloaded(QNetworkReply* pReply);
    void updateDownloadProgress(qint64, qint64);
    void httpReadyRead();

private:

    QNetworkAccessManager *m_WebCtrl;
    QNetworkReply *m_reply;
    QByteArray m_DownloadedData;
    QFile *m_destFile;
    bool m_httpRequestAborted;
    bool m_shouldUncompress;

};

#endif // FILEDOWNLOADER_H
