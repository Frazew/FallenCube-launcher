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
    jre32 = *new QUrl();
    jdk32 = *new QUrl();
    jre64 = *new QUrl();
    jdk64 = *new QUrl();
    ui->status->setText("Téléchargement des métadonnées...");
    QUrl jsonUrl("http://download.fallencube.fr/launcher/launcher.json");
    m_file = new FileDownloader(jsonUrl, QString("launcher.json"), false, this);
    connect(m_file, SIGNAL(downloaded()), SLOT(loadJson()));
}

void MainWindow::loadJson()
{
     ui->progress->setValue(1);
     ui->status->setText("Analyse des fichiers à télécharger...");
     QFile launcher("launcher.json");
     launcher.open(QIODevice::ReadOnly);
     QString strReply = (QString)launcher.readAll();
     launcher.close();
     QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
     QJsonObject jsonObject = jsonResponse.object();
     QJsonObject windows = jsonObject["windows"].toObject();
     jre32 = windows["32"].toObject()["jre"].toObject()["url"].toString();
     jre64 = windows["64"].toObject()["jre"].toObject()["url"].toString();
     jdk32 = windows["32"].toObject()["jdk"].toObject()["url"].toString();
     jdk64 = windows["64"].toObject()["jdk"].toObject()["url"].toString();
     ui->progress->setValue(5);
     ui->status->setText("Téléchargement des fichiers... 1/2");
     launcher.remove();
     m_file = new FileDownloader(jre32, QString("jre32.lzma"), true, this);
     connect(m_file, SIGNAL(update(qint64, qint64)), SLOT(updateProgressBar(qint64, qint64)));
     connect(m_file, SIGNAL(downloaded()), SLOT(saveLzma()));
}

void MainWindow::saveLzma()
{
    ZipDecompress zip("jre32.lzma", "java/");
    ui->progress->setValue(0);
    ui->status->setText("Téléchargement des fichiers... 2/2");
    QFile::remove("jre32.lzma");
    QUrl launcherUrl("http://download.fallencube.fr/launcher/launcher.jar");
    m_file = new FileDownloader(launcherUrl, QString("launcher.jar"), false, this);
    connect(m_file, SIGNAL(update(qint64, qint64)), SLOT(updateProgressBar(qint64, qint64)));
    connect(m_file, SIGNAL(downloaded()), SLOT(saveLauncher()));
}

void MainWindow::saveLauncher()
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

