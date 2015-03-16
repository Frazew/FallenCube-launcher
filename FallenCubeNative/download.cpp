#include "download.h"

Download::Download(QUrl url, QString localName, bool comp)
{
    m_url = url;
    m_name = localName;
    m_compressed = comp;
}

QUrl Download::getUrl() const {
    return m_url;
}

QString Download::getName() const {
    return m_name;
}

bool Download::isCompressed() const {
    return m_compressed;
}
