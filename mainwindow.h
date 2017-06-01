#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QListWidget>

namespace Ui {
class MainWindow;
class InstallThread;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void processOutput();
    void on_btn_install_clicked();

    void on_sync_clicked();

private:
    Ui::MainWindow *ui;
    void addAppsToList();
    void addSignalsSlots();
    void checkIfProgramsExists();
    void installQueue();

    QMap< QString, QStringList > AppList;
    QProcess *terminal;
    QByteArray terminalOutput;
    QByteArray terminalOutputErr;
    QVector<QListWidget*> *listArr;
    QStringList *appsWillInstall;
};
#endif // MAINWINDOW_H
