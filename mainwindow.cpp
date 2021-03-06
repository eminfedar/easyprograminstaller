#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>
#include <QProcess>
#include <QMessageBox>
#include <string>
#include <QDateTime>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

void MainWindow::addAppsToList(){
    // Clear
    AppList.clear();
    for (int i = 0; i < listArr->count(); ++i)
        listArr->at(i)->clear();

    QString path = "/home/" + username + "/.config/easyprograminstaller/applist.json";
    QFile applistFile(path);
    if( !applistFile.open(QFile::ReadOnly) ){
        terminal->start((QString)("/bin/sh -c \"wget -O /home/" + username + "/.config/easyprograminstaller/applist.yaml 'https://github.com/eminfedar/easyprograminstaller/raw/master/applist.json' -q --no-check-certificate\""));
        terminal->waitForFinished();
        terminal->close();

        applistFile.open(QFile::ReadOnly);
    }

    QByteArray applistData = applistFile.readAll();
    QJsonDocument applistJSONDoc( QJsonDocument::fromJson(applistData) );
    QJsonObject applistJSONObj = applistJSONDoc.object();

    for (const QString category : (QStringList) applistJSONObj.keys()) {
        for (const QString appName : (QStringList) ((QJsonValueRef)applistJSONObj[category]).toObject().keys() ) {

            if(category == "Developers"){
                ui->list_developers->addItem(appName);
            }else if(category == "General"){
                ui->list_general->addItem(appName);
            }else if(category == "Tools"){
                ui->list_tools->addItem(appName);
            }else if(category == "System Management"){
                ui->list_system->addItem(appName);
            }

            QJsonObject categoryObj = ((QJsonValueRef)applistJSONObj[category]).toObject();
            QJsonValue appCommands = (QJsonValueRef)(categoryObj[appName]);
            QStringList appCommandsArr = appCommands.toVariant().toStringList();
            for(int i=0; i < appCommandsArr.size(); i++){
                AppList[appName].append(appCommandsArr[i]);
            }

        }
    }


    // SETTING ITEM FLAGS & SORTING
    for (int a = 0; a < listArr->count(); ++a) {
        listArr->at(a)->sortItems();

        for (int i = 0; i < listArr->at(a)->count(); ++i) {
            listArr->at(a)->item(i)->setFlags(Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
            listArr->at(a)->item(i)->setCheckState(Qt::Unchecked);
        }
    }

}

void MainWindow::addSignalsSlots(){
    connect(terminal, SIGNAL(readyReadStandardOutput()), this, SLOT( processOutput() ) );
    connect(terminal, SIGNAL(readyReadStandardError() ), this, SLOT( processOutput() ) );
}

void MainWindow::checkIfProgramsExists(){
    QString appName = "";

    for (int a = 0; a < listArr->count(); ++a) {
        QListWidget* list = listArr->at(a);

        for (int i = 0; i < list->count(); ++i) {
            appName = list->item(i)->text();

            if(AppList.contains(appName)){

                //terminal->start("/bin/sh", QStringList() << "-c" << AppList.value(appName).at(AppList.value(appName).count()-1));
                terminal->start((QString)("/bin/bash -c \"" + AppList.value(appName).at(AppList.value(appName).count()-1)) + "\"");
                terminal->waitForFinished();

                //qDebug() << appName << " : " << terminalOutput << " - " << terminalOutput.length();
                if(terminalOutput.length() > 0 && terminalOutput != "--- |FINISHED| ---\n"){
                    list->item(i)->setForeground(QColor(0,150,0));
                    list->item(i)->setFlags(list->item(i)->flags().setFlag(Qt::ItemIsEnabled, false));
                    list->item(i)->setCheckState(Qt::Checked);
                }

                terminalOutput.clear();
                terminal->close();

            }
        }
    }
    ui->txt_output->setText("Ready.");
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //qint64 stamp = QDateTime::currentMSecsSinceEpoch();

    ui->txt_output->setText("Preparing the Program...");

    username = qgetenv("USER");
    if (username.isEmpty())
        username = qgetenv("USERNAME");

    listArr = new QVector<QListWidget*>();
    listArr->append( (QListWidget*)ui->list_developers );
    listArr->append( (QListWidget*)ui->list_general );
    listArr->append( (QListWidget*)ui->list_tools );
    listArr->append( (QListWidget*)ui->list_system );

    appsWillInstall = new QStringList();

    terminal = new QProcess(this);
    terminal->start((QString)("/bin/sh -c \"mkdir -p ~/.config/easyprograminstaller/downloaded\""));
    terminal->waitForFinished();
    terminal->close();

    addAppsToList();
    addSignalsSlots();
    checkIfProgramsExists();


    ui->txt_output->setText("Ready.");

    //qint64 newstamp = QDateTime::currentMSecsSinceEpoch();
    //qDebug() << "Ms difference : " << (newstamp - stamp);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// APP INSTALLATION
void MainWindow::installQueue(){
    if(appsWillInstall->length() == 0) return;

    QStringList appCommand = AppList.value(appsWillInstall->first());
    appCommand.removeLast();// Because the last one is for checking if the app installed
    appCommand.push_back("echo '--- |FINISHED| ---'");
    for (int i = 0; i < appCommand.count(); ++i) {
        QString cmd = appCommand.at(i);
        //qDebug() << appCommand.at(i);
        cmd.replace("$USER", username);
        appCommand[i] = cmd;
        //qDebug() << appCommand.at(i);
    }

    ui->btn_install->setEnabled(false);
    for(int i = 0; i < listArr->count(); i++){
        listArr->at(i)->setEnabled(false);
    }
    ui->btn_sync->setEnabled(false);

    terminal->start((QString)("pkexec /bin/sh -c \"" + appCommand.join(" && ") + "\""));

    if(appsWillInstall->length() > 0)
        appsWillInstall->removeFirst();
}


void MainWindow::processOutput(){
    terminalOutput = terminal->readAllStandardOutput();
    terminalOutputErr = terminal->readAllStandardError();

    // To Show Percentage of the Download
    QString errOutput = (QString)terminalOutputErr;
    if(errOutput.contains(QRegExp("[0-9]%"))){
        errOutput.replace('.',"");
        errOutput.replace("\n","");
        ui->txt_outputerr->setText("Downloading... " + errOutput.split("%")[0] + "%");
    }

    // To Show info about installing
    QString preparedText = terminalOutput.left(70);
    preparedText.replace("\n","");
    ui->txt_output->setText(preparedText);
    //qDebug() << terminalOutput;
    //qDebug() << terminalOutputErr;

    const QString terminalOutputConst = terminalOutput;

    // If all commands finished.
    if(terminalOutputConst.indexOf("--- |FINISHED| ---") > -1){
        terminal->close();
        ui->txt_outputerr->setText("Ready");
        checkIfProgramsExists();
        installQueue();
        ui->btn_install->setEnabled(true);
        for(int i = 0; i < listArr->count(); i++){
            listArr->at(i)->setEnabled(true);
        }
        ui->btn_sync->setEnabled(true);
        ui->centralWidget->repaint();
    }
    // Check Download Folder
    if(terminalOutputConst.indexOf("--CHECKDOWNLOADFOLDER--") > -1){
        QMessageBox::information(this, "Info", "Download Complete.\n\nYou can access the downloaded files from:\n~/.config/easyprograminstaller/downloaded");
    }
    // Extracted to /opt
    if(terminalOutputConst.indexOf("--EXTRACTEDTOOPT--") > -1){
        QMessageBox::information(this, "Info", "Files extracted to the /opt/ folder.\n\nYou can access from there.");
    }

}


void MainWindow::on_btn_install_clicked()
{
    // Cache Lists
    appsWillInstall->clear();
    QListWidget * list;
    for (int a = 0; a < listArr->count(); ++a) {
        list = listArr->at(a);

        for (int i = 0; i < list->count(); ++i) {
            if(list->item(i)->checkState() && list->item(i)->flags().testFlag(Qt::ItemIsEnabled)){
                appsWillInstall->append(list->item(i)->text());
            }
        }
    }

    if(appsWillInstall->length() == 0) return;

    QMessageBox::StandardButton answer = QMessageBox::question(this, "Check the apps:", "These apps will install:\n\n" + appsWillInstall->join(", ") + "\n\nSure?", QMessageBox::Yes|QMessageBox::No);

    if(answer == QMessageBox::Yes)
        installQueue();
}

void MainWindow::on_btn_sync_clicked(){
    for (int i = 0; i < listArr->count(); ++i) {
        listArr->at(i)->clear();
        listArr->at(i)->addItem("Please Wait. Downloading...");
        listArr->at(i)->repaint();
    }
    ui->btn_install->repaint(); // This is just for refreshing the last list. Because it is not refreshing the last one. So we make this last one.

    terminal->start((QString)("/bin/sh -c \"mv ~/.config/easyprograminstaller/applist.yaml ~/.config/easyprograminstaller/applist.yaml.old; wget -O /home/" + username + "/.config/easyprograminstaller/applist.yaml 'https://raw.githubusercontent.com/eminfedar/easyprograminstaller/master/applist.yaml' -q --no-check-certificate\""));
    terminal->waitForFinished();
    terminal->close();

    addAppsToList();
    checkIfProgramsExists();
    QMessageBox::information(this, "Info", "App List UPDATED (~/.config/easyprograminstaller/applist.yaml)\nOld list secured in: 'applist.yaml.old'");
}
