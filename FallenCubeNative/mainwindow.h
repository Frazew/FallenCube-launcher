#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include "filedownloader.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    FileDownloader *m_file;
    Ui::MainWindow *ui;
    QUrl jdk64;
    QUrl jdk32;
    QUrl jre64;
    QUrl jre32;

private slots:
    void loadJson();
    void saveLzma();
    void saveLauncher();
    void updateProgressBar(qint64, qint64);
};

#endif // MAINWINDOW_H
