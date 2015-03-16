#ifndef DOWNLOAD_H
#define DOWNLOAD_H

#include <QUrl>
#include <QString>

class Download
{
public:
    Download(QUrl url, QString localName, bool compress);
    QUrl getUrl() const;
    QString getName() const;
    bool isCompressed() const;

private:
    bool m_compressed;
    QUrl m_url;
    QString m_name;
};

#endif // DOWNLOAD_H
