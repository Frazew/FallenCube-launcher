#include "filedownloader.h"
#include <QMessageBox>

FileDownloader::FileDownloader(QUrl imageUrl, QString file, bool compress, QObject *parent) :
    QObject(parent)
{
    httpRequestAborted = false;
    shouldUncompress = compress;
    destFile = new QFile(file);

    if (!destFile->open(QIODevice::WriteOnly)) {
        delete destFile;
        destFile = 0;
        return;
    }
    m_WebCtrl = new QNetworkAccessManager(this);
    connect(m_WebCtrl, SIGNAL(finished(QNetworkReply*)),
                SLOT(fileDownloaded(QNetworkReply*)));

    QNetworkRequest request(imageUrl);
    reply = m_WebCtrl->get(request);
    connect(reply, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(updateDownloadProgress(qint64,qint64)));
    connect(reply, SIGNAL(readyRead()), this, SLOT(httpReadyRead()));
}

void FileDownloader::httpReadyRead() {
    if (destFile) destFile->write(reply->readAll());
}

void FileDownloader::updateDownloadProgress(qint64 bytesRead, qint64 totalBytes) {
    if (httpRequestAborted) return;
    emit update(bytesRead, totalBytes);
}

void FileDownloader::fileDownloaded(QNetworkReply* pReply)
{
    m_DownloadedData = pReply->readAll();
    destFile->flush();
    if (destFile) destFile->close();
    if (shouldUncompress) {
        destFile->open(QIODevice::ReadOnly);
        QByteArray source(destFile->readAll());
        destFile->close();
        destFile->open(QFile::ReadWrite | QIODevice::Truncate);
        destFile->write(qUncompress(source));
        destFile->close();
    }
    pReply->deleteLater();
    emit downloaded();
}
