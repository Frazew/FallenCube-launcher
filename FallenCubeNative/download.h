#ifndef DOWNLOAD_H
#define DOWNLOAD_H

#include <QObject>
#include <QUrl>
#include <QString>

class Download : public QObject
{
    Q_OBJECT
public:
    Download(QUrl url, QString localName, bool compress, QObject *parent = 0);
    QUrl getUrl();
    QString getName();
    bool isCompressed();

private:
    bool m_compressed;
    QUrl m_url;
    QString m_name;
signals:

public slots:
};

#endif // DOWNLOAD_H
