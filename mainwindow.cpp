#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>
#include <QProcess>
#include <QMessageBox>
#include "yaml-cpp/yaml.h"
#include <string>


void MainWindow::addAppsToList(){

    ui->list_developers->clear();
    ui->list_general->clear();
    ui->list_tools->clear();
    ui->list_system->clear();

    YAML::Node applist = YAML::LoadFile("/home/eminfedar/.config/easyprograminstaller/applist.yaml");

    for(YAML::const_iterator categories = applist.begin(); categories != applist.end(); ++categories){
        std::string category_name = categories->first.as<std::string>();
        YAML::Node category = categories->second.as<YAML::Node>();

        for (YAML::const_iterator app = category.begin(); app != category.end(); ++app) {
            std::string app_name = app->first.as<std::string>();
            YAML::Node commandlist = app->second.as<YAML::Node>();

            if(category_name == "Developers"){
                ui->list_developers->addItem((QString)app_name.c_str());
            }else if(category_name == "General"){
                ui->list_general->addItem((QString)app_name.c_str());
            }else if(category_name == "Tools"){
                ui->list_tools->addItem((QString)app_name.c_str());
            }else if(category_name == "System Management"){
                ui->list_system->addItem((QString)app_name.c_str());
            }

            for (YAML::const_iterator commands = commandlist.begin(); commands != commandlist.end(); ++commands) {
                std::string command = commands->as<std::string>();
                QString appName = (QString)app_name.c_str();

                AppList[appName].append(command.c_str());
            }
        }
    }

    // SETTING ITEMS FLAGS & SORTING
    ui->list_developers->sortItems();
    for (int i = 0; i < ui->list_developers->count(); ++i) {
        ui->list_developers->item(i)->setFlags(Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        ui->list_developers->item(i)->setCheckState(Qt::Unchecked);
    }

    ui->list_general->sortItems();
    for (int i = 0; i < ui->list_general->count(); ++i) {
        ui->list_general->item(i)->setFlags(Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        ui->list_general->item(i)->setCheckState(Qt::Unchecked);
    }

    ui->list_tools->sortItems();
    for (int i = 0; i < ui->list_tools->count(); ++i) {
        ui->list_tools->item(i)->setFlags(Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        ui->list_tools->item(i)->setCheckState(Qt::Unchecked);
    }

    ui->list_system->sortItems();
    for (int i = 0; i < ui->list_system->count(); ++i) {
        ui->list_system->item(i)->setFlags(Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        ui->list_system->item(i)->setCheckState(Qt::Unchecked);
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

                terminal->start("/bin/sh", QStringList() << "-c" << AppList.value(appName).at(AppList.value(appName).count()-1));
                terminal->waitForFinished();


                if(terminalOutput.length() > 0 && terminalOutput != "--- |FINISHED| ---\n"){
                    list->item(i)->setForeground(QColor(0,150,0));
                    list->item(i)->setFlags(!Qt::ItemIsEnabled);
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

    ui->txt_output->setText("Preparing the Program...");


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
}

MainWindow::~MainWindow()
{
    delete ui;
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

    //qDebug() << terminalOutputErr;
    ui->txt_output->setText(terminalOutput);

    // If commands finished.
    if(terminalOutput == "--- |FINISHED| ---\n"){
        terminal->close();
        ui->txt_outputerr->setText("");
        checkIfProgramsExists();
        installQueue();
        ui->btn_install->setEnabled(true);
    }else if(terminalOutput == "--CHECKDOWNLOADFOLDER--\n"){
        QString username = qgetenv("USER");
        QMessageBox::information(this, "Info", "Download Complete.\n\nYou can access the downloaded files from:\n/home/" + username + "/.config/easyprograminstaller/downloaded");
    }else if(terminalOutput == "--EXTRACTEDTOOPT--\n"){
        QMessageBox::information(this, "Info", "Files extracted to the /opt/ folder.\n\nYou can access from there.");
    }
}

void MainWindow::installQueue(){
    if(appsWillInstall->length() == 0) return;

    QStringList appCommand = AppList.value(appsWillInstall->first());
    appCommand.removeLast();// Because the last one is for checking if the app installed
    appCommand.push_back("echo '--- |FINISHED| ---'");

    ui->btn_install->setEnabled(false);

    terminal->start((QString)("/bin/sh -c \"" + appCommand.join(" && ") + "\""));

    if(appsWillInstall->length() > 0)
        appsWillInstall->removeFirst();
}


void MainWindow::on_btn_install_clicked()
{

    // Cache Lists
    appsWillInstall->clear();
    QListWidget * list;
    for (int a = 0; a < listArr->count(); ++a) {
        list = listArr->at(a);

        for (int i = 0; i < list->count(); ++i) {
            if(list->item(i)->checkState() && list->item(i)->flags() != Qt::NoItemFlags){
                appsWillInstall->append(list->item(i)->text());
            }
        }
    }

    if(appsWillInstall->length() == 0) return;

    QMessageBox::StandardButton answer = QMessageBox::question(this, "Check the apps:", "These apps will install:\n\n" + appsWillInstall->join(", ") + "\n\nSure?", QMessageBox::Yes|QMessageBox::No);

    if(answer == QMessageBox::Yes)
        installQueue();
}

void MainWindow::on_sync_clicked()
{
    for (int i = 0; i < listArr->count(); ++i) {
        listArr->at(i)->clear();
        listArr->at(i)->addItem("Please Wait. Downloading...");
        listArr->at(i)->repaint();
    }
    ui->btn_install->repaint(); // This is just for refreshing the last list. Because it is not refreshing the last one. So we make this last one.

    terminal->start((QString)("/bin/sh -c \"mv ~/.config/easyprograminstaller/applist.yaml ~/.config/easyprograminstaller/applist.yaml.old; wget -O /home/eminfedar/.config/easyprograminstaller/applist.yaml 'https://github.com/eminfedar/easyprograminstaller/raw/master/applist.yaml' -q --no-check-certificate\""));
    terminal->waitForFinished();

    addAppsToList();
    checkIfProgramsExists();
    ui->txt_output->setText("App List UPDATED (~/.config/easyprograminstaller/applist.yaml)\nOld list secured in: 'applist.yaml.old'");
}
