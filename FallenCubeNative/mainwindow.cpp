#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "filedownloader.h"
#include "zipdecompress.h"
#include <QFile>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QProcess>
#include <QDir>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->progress->setValue(0);

    ui->status->setText("Téléchargement des métadonnées...");
    QUrl jsonUrl("http://download.fallencube.fr/launcher/launcher.json");
    m_file = new FileDownloader(jsonUrl, QString("launcher.json"), false, this);
    connect(m_file, SIGNAL(downloaded()), SLOT(loadJson()));
}

void MainWindow::loadJson()
{
     ui->status->setText("Analyse des fichiers à télécharger...");

     QFile launcher("launcher.json");
     launcher.open(QIODevice::ReadOnly);
     QString strReply = (QString)launcher.readAll();
     launcher.close();

     QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
     QJsonObject jsonObject = jsonResponse.object();
     QJsonObject windows = jsonObject["windows"].toObject();

     m_jre32 = windows["32"].toObject()["jre"].toObject()["url"].toString();
     m_jre64 = windows["64"].toObject()["jre"].toObject()["url"].toString();
     m_jdk32 = windows["32"].toObject()["jdk"].toObject()["url"].toString();
     m_jdk64 = windows["64"].toObject()["jdk"].toObject()["url"].toString();

     launcher.remove();
     QUrl launcherUrl("http://download.fallencube.fr/launcher/launcher.jar");

     m_downloadlist.insert("Java", *new Download(m_jre32, "jre32.lzma", true));
     m_downloadlist.insert("Launcher", *new Download(launcherUrl, "launcher.jar", false));
     downloadRequired();
}

void MainWindow::downloadRequired() {

    QMapIterator<QString, Download> iter(m_downloadlist);
    QString status("Téléchargement des fichiers... %1/%2");
    QEventLoop loop;
    int count = 0;
    while(iter.hasNext()) {
        iter.next();
        count++;
        ui->status->setText(status.arg(QString::number(count), QString::number(m_downloadlist.size())));
        m_file = new FileDownloader(iter.value().getUrl(), iter.value().getName(), iter.value().isCompressed(), this);
        connect(m_file, SIGNAL(update(qint64, qint64)), SLOT(updateProgressBar(qint64, qint64)));
        connect(m_file, SIGNAL(downloaded()), &loop, SLOT(quit()));
        loop.exec();
    }
    processDownloaded();
}

void MainWindow::processDownloaded()
{
    new ZipDecompress("jre32.lzma", "java/");
    launch();
}

void MainWindow::launch()
{
    QString java = "./java/bin/javaw.exe";
    QStringList arguments;
    arguments << "-classpath" << "launcher.jar" << "net.fallencube.launcher.Launcher";
    QProcess::startDetached(java, arguments);
    close();
}

void MainWindow::updateProgressBar(qint64 bytesRead, qint64 totalBytes) {
    ui->progress->setMaximum(totalBytes);
    ui->progress->setValue(bytesRead);
}

MainWindow::~MainWindow()
{
    delete ui;
}

