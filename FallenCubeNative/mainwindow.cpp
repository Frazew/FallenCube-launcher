#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "filedownloader.h"
#include "zipdecompress.h"
#include <QFile>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->progress->setValue(0);
    ui->status->setText("Téléchargement des métadonnées...");
    QUrl jsonUrl("http://download.fallencube.fr/launcher/launcher.json");
    //m_file = new FileDownloader(jsonUrl, this);
    //connect(m_file, SIGNAL(downloaded()), SLOT(loadJson()));
    ZipDecompress zip("jre32.lzma", "java/");
}

void MainWindow::loadJson()
{
     ui->progress->setValue(1);
     ui->status->setText("Analyse des fichiers à télécharger...");
     QString strReply = (QString)m_file->downloadedData();
     QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
     QJsonObject jsonObject = jsonResponse.object();
     QJsonObject windows = jsonObject["windows"].toObject();
     jre32 = new QUrl(windows["32"].toObject()["jre"].toObject()["url"].toString());
     jre64 = new QUrl(windows["64"].toObject()["jre"].toObject()["url"].toString());
     jdk32 = new QUrl(windows["32"].toObject()["jdk"].toObject()["url"].toString());
     jdk64 = new QUrl(windows["64"].toObject()["jdk"].toObject()["url"].toString());
     ui->progress->setValue(5);
     ui->status->setText("Téléchargement des fichiers... 1/2");
     m_file = new FileDownloader(*jre32, this);
     connect(m_file, SIGNAL(update(qint64, qint64)), SLOT(updateProgressBar(qint64, qint64)));
     connect(m_file, SIGNAL(downloaded()), SLOT(saveLzma()));
}

void MainWindow::saveLzma()
{
    QFile file("jre32.lzma");
    file.open(QIODevice::WriteOnly);
    file.write(qUncompress(m_file->downloadedData()));
    file.close();
    ZipDecompress zip("jre32.lzma", "java/");

    ui->progress->setValue(0);
    ui->status->setText("Téléchargement des fichiers... 2/2");
    QUrl launcherUrl("http://download.fallencube.fr/launcher/launcher.jar");
    m_file = new FileDownloader(launcherUrl, this);
    connect(m_file, SIGNAL(update(qint64, qint64)), SLOT(updateProgressBar(qint64, qint64)));
    connect(m_file, SIGNAL(downloaded()), SLOT(saveLauncher()));
}

void MainWindow::saveLauncher()
{
    QFile file("launcher.jar");
    file.open(QIODevice::WriteOnly);
    file.write(m_file->downloadedData());
    file.close();
}

void MainWindow::updateProgressBar(qint64 bytesRead, qint64 totalBytes) {
    ui->progress->setMaximum(totalBytes);
    ui->progress->setValue(bytesRead);
}

MainWindow::~MainWindow()
{
    delete ui;
}

