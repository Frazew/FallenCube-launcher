#include "download.h"

Download::Download(QUrl url, QString localName, bool comp, QObject *parent) : QObject(parent)
{
    m_url = url;
    m_name = localName;
    m_compressed = comp;
}

QUrl Download::getUrl() {
    return m_url;
}

QString Download::getName() {
    return m_name;
}

bool Download::isCompressed() {
    return m_compressed;
}
