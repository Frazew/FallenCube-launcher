#include "filedownloader.h"
#include <QMessageBox>

FileDownloader::FileDownloader(QUrl url, QString file, bool compress, QObject *parent) :
    m_httpRequestAborted(false), m_destFile(new QFile(file)), m_shouldUncompress(compress), QObject(parent)
{
    if (!m_destFile->open(QIODevice::WriteOnly)) {
        delete m_destFile;
        m_destFile = 0;
        return;
    }
    m_WebCtrl = new QNetworkAccessManager(this);
    connect(m_WebCtrl, SIGNAL(finished(QNetworkReply*)), SLOT(fileDownloaded(QNetworkReply*)));

    QNetworkRequest request(url);
    m_reply = m_WebCtrl->get(request);
    connect(m_reply, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(updateDownloadProgress(qint64,qint64)));
    connect(m_reply, SIGNAL(readyRead()), this, SLOT(httpReadyRead()));
}

void FileDownloader::httpReadyRead() {
    if (m_destFile) m_destFile->write(m_reply->readAll());
}

void FileDownloader::updateDownloadProgress(qint64 bytesRead, qint64 totalBytes) {
    if (m_httpRequestAborted) return;
    emit update(bytesRead, totalBytes);
}

void FileDownloader::fileDownloaded(QNetworkReply* pReply)
{
    m_DownloadedData = pReply->readAll();
    m_destFile->flush();
    if (m_destFile) m_destFile->close();
    if (m_shouldUncompress) {
        m_destFile->open(QIODevice::ReadOnly);
        QByteArray source(m_destFile->readAll());
        m_destFile->close();
        m_destFile->open(QFile::ReadWrite | QIODevice::Truncate);
        m_destFile->write(qUncompress(source));
        m_destFile->close();
    }
    pReply->deleteLater();
    emit downloaded();
}
