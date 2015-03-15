#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include "filedownloader.h"
#include "download.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void downloadRequired();
    void processDownloaded();
    void launch();
    ~MainWindow();

private:
    FileDownloader *m_file;
    Ui::MainWindow *ui;
    QUrl jdk64;
    QUrl jdk32;
    QUrl jre64;
    QUrl jre32;
    QMap<QString, Download *> downloadlist;

private slots:
    void loadJson();
    void updateProgressBar(qint64, qint64);
};

#endif // MAINWINDOW_H
