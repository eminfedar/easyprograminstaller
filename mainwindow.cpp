#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>
#include <QProcess>
#include <QMessageBox>

void MainWindow::addAppsToList(){

    // --- | EASY PROGRAM INSTALLER | ---
    //
    // HOW CAN I ADD A PROGRAM TO THE LIST
    // 1-> ADD THE PROGRAM'S NAME TO THE RELATED LIST
    // 2-> ADD THE PROGRAM'S NAME & INSTALL COMMANDS TO THE 'AppList' WITH '.insert()' COMMAND
    // 3-> !!!!!NAME IN ITEMS AND APPLIST MUST BE EQUAL!!!!!
    // 4-> DONE
    //
    // CAREFUL: YOU SHOULD USE "-y" TAGS OR NOT ANYTHING CAN FREEZE THE TERMINAL.

    // LIST_DEVELOPERS
    ui->list_developers->addItems({"Android Studio"
                                  ,"Arduino IDE"
                                  ,"Atom Text Editor"
                                  ,"Eclipse Installer"
                                  ,"Mono Develop"
                                  ,"NetBeans IDE"
                                  //,"IntelliJ IDEA (Not Ready)"
                                  ,"PyCharm"
                                  //,"PhpStorm (Not Ready)"
                                  ,"Sublime Text"
                                  ,"Qt 5"
                                  ,"Qt Creator"
                                  ,"Visual Studio Code"
                                  ,"Vim"
                                  ,"Java Runtime Environment"
                                  ,"Java Development Kit"
                                  ,"OpenJRE 8"
                                  ,"OpenJDK 8"
                                  });
    // LIST_GENERAL
    ui->list_general->addItems({"Google Chrome"
                                  ,"Mozilla Firefox"
                                  ,"Vivaldi"
                                  ,"Opera"
                                  ,"Spotify"
                                  ,"VLC Media Player"
                                  ,"GIMP Image Editor"
                                  ,"Pitivi Video Editor"
                                  ,"Telegram Desktop"
                                  ,"WhatsApp Desktop"
                                  ,"Skype"
                                  ,"TeamViewer"
                                  ,"VirtualBox"
                                  });
    // LIST_TOOLS
    ui->list_tools->addItems({"Unity Tweak Tool"
                                  ,"Gnome Tweak Tool"
                                  ,"Conky"
                                  ,"FileZilla"
                                  ,"RecordMyDesktop"
                                  ,"dconf Editor"
                                  ,"Wine"
                                  ,"Cairo Dock"
                                  ,"Docky"
                                  ,"Plank"
                                  });
    // LIST_SYSTEM
    ui->list_system->addItems({"GParted"
                                  ,"Boot Repair"
                                  });

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

void MainWindow::configureAppList(){

    // DESC: {"commands for installing" .... , "commands for checking if exists"}
    // NOTE: Install scripts mustn't pause, so please use '-y' arg.

    // LIST_DEVELOPERS
    AppList.insert("Android Studio", {"sudo apt install unzip libc6:i386 libncurses5:i386 libstdc++6:i386 lib32z1 libbz2-1.0:i386 -y"
                                        ,"wget -O /home/$USER/.config/easyprograminstaller/downloaded/androidstudio.zip \"https://dl.google.com/dl/android/studio/ide-zips/2.3.2.0/android-studio-ide-162.3934792-linux.zip\" -q --no-check-certificate --show-progress --progress=dot"
                                        ,"cd /home/$USER/.config/easyprograminstaller/downloaded"
                                        ,"unzip androidstudio.zip -d /usr/local"
                                        ,"cd /usr/local/android-studio/bin"
                                        ,"echo '--CHECKDOWNLOADFOLDER--'"
                                        ,"./studio.sh"
                                        ,"[ -d /usr/local/android-studio ] && echo 'exists'"});

    AppList.insert("Arduino IDE", {" sudo apt install arduino arduino-core -y"
                                        ,"dpkg -l | grep -o 'ii  arduino'"});

    AppList.insert("Atom Text Editor", {"wget -O /home/$USER/.config/easyprograminstaller/downloaded/atom.deb \"https://atom.io/download/deb\" -q --no-check-certificate --show-progress --progress=dot"
                                        ,"sudo dpkg -i /home/$USER/.config/easyprograminstaller/downloaded/atom.deb"
                                        ,"echo '--CHECKDOWNLOADFOLDER--'"
                                        ,"dpkg -l | grep -o 'ii  atom'"});

    AppList.insert("Eclipse Installer", {"wget -O /home/$USER/.config/easyprograminstaller/downloaded/eclipse.tar.gz \"http://ftp-stud.fht-esslingen.de/pub/Mirrors/eclipse/oomph/epp/neon/R3/eclipse-inst-linux64.tar.gz\" -q --no-check-certificate --show-progress --progress=dot"
                                        ,"cd /home/$USER/.config/easyprograminstaller/downloaded"
                                        ,"tar xf eclipse.tar.gz"
                                        ,"cd eclipse-installer"
                                        ,"echo '--CHECKDOWNLOADFOLDER--'"
                                        ,"(./eclipse-inst &)"
                                        ,"[ -d /home/$USER/.config/easyprograminstaller/downloaded/eclipse-installer ] && echo 'exists'"});

    AppList.insert("Mono Develop", {"sudo apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv-keys 3FA7E0328081BFF6A14DA29AA6A19B38D3D831EF"
                                        ,"echo \"deb http://download.mono-project.com/repo/ubuntu xenial main\" | sudo tee /etc/apt/sources.list.d/mono-official.list"
                                        ,"sudo apt update"
                                        ,"sudo apt install mono-devel"
                                        ,"dpkg -l | grep -o 'ii  mono-devel'"});

    AppList.insert("NetBeans IDE", {"sudo apt install netbeans -y"
                                        ,"dpkg -l | grep -o 'ii  netbeans'"});

    AppList.insert("IntelliJ IDEA", {"wget -O /home/$USER/.config/easyprograminstaller/downloaded/intellijidea.tar.gz \"https://download.jetbrains.com/idea/ideaIC-2017.1.3-no-jdk.tar.gz\" -q --no-check-certificate --show-progress --progress=dot"
                                        ,"cd /home/$USER/.config/easyprograminstaller/downloaded/"
                                        ,"tar xf intellijidea.tar.gz -C /opt/"
                                        ,"echo '--EXTRACTEDTOOPT--'"
                                        ,"[ -d /home/$USER/.config/easyprograminstaller/downloaded/intellijidea.tar.gz ] && echo 'exists'"});

    AppList.insert("PyCharm", {"sudo add-apt-repository ppa:mystic-mirage/pycharm"
                                        ,"sudo apt update"
                                        ,"sudo apt install pycharm-community"
                                        ,"dpkg -l | grep -o 'ii  pycharm-community'"});

    AppList.insert("PhpStorm", {"sudo apt install vlc -y"
                                        ,"dpkg -l | grep -o 'ii  vlc'"});

    AppList.insert("Sublime Text", {"wget -O /home/$USER/.config/easyprograminstaller/downloaded/sublime.deb \"https://download.sublimetext.com/sublime-text_build-3126_amd64.deb\" -q --no-check-certificate --show-progress --progress=dot"
                                        ,"sudo dpkg -i /home/$USER/.config/easyprograminstaller/downloaded/sublime.deb"
                                        ,"echo '--CHECKDOWNLOADFOLDER--'"
                                        ,"dpkg -l | grep -o 'ii  vlc'"});

    AppList.insert("Qt 5", {"sudo apt install qt5-default -y"
                                        ,"dpkg -l | grep -o 'ii  qt5-default'"});

    AppList.insert("Qt Creator", {"sudo apt install qtcreator -y"
                                        ,"dpkg -l | grep -o 'ii  qtcreator'"});

    AppList.insert("Visual Studio Code", {"wget -O /home/$USER/.config/easyprograminstaller/downloaded/vscode.deb \"https://az764295.vo.msecnd.net/stable/19222cdc84ce72202478ba1cec5cb557b71163de/code_1.12.2-1494422229_amd64.deb\" -q --no-check-certificate --show-progress --progress=dot"
                                        ,"sudo dpkg -i /home/$USER/.config/easyprograminstaller/downloaded/vscode.deb"
                                        ,"echo '--CHECKDOWNLOADFOLDER--'"
                                        ,"dpkg -l | grep -o 'ii  code'"});

    AppList.insert("Vim", {"sudo apt install vim -y"
                                        ,"dpkg -l | grep -o 'ii  vim'"});

    AppList.insert("Java Runtime Environment", {"sudo apt install default-jre -y"
                                        ,"dpkg -l | grep -o 'ii  default-jre'"});

    AppList.insert("Java Development Kit", {"sudo apt install default-jdk -y"
                                        ,"dpkg -l | grep -o 'ii  default-jdk'"});

    AppList.insert("OpenJRE 8", {"sudo apt install openjdk-8-jre -y"
                                        ,"dpkg -l | grep -o 'ii  openjdk-8-jre'"});

    AppList.insert("OpenJDK 8", {"sudo apt install openjdk-8-jdk -y"
                                        ,"dpkg -l | grep -o 'ii  openjdk-8-jdk'"});


    // LIST_GENERAL
    AppList.insert("Google Chrome", {"wget -O /home/$USER/.config/easyprograminstaller/downloaded/googlechrome.deb \"https://dl.google.com/linux/direct/google-chrome-stable_current_amd64.deb\" -q --no-check-certificate --show-progress --progress=dot"
                                        ,"sudo dpkg -i /home/$USER/.config/easyprograminstaller/downloaded/googlechrome.deb"
                                        ,"echo '--CHECKDOWNLOADFOLDER--'"
                                        ,"dpkg -l | grep -o 'ii  google-chrome'"});

    AppList.insert("Mozilla Firefox", {"sudo apt install firefox -y"
                                        ,"dpkg -l | grep -o 'ii  firefox'"});

    AppList.insert("Vivaldi", {"wget -O /home/$USER/.config/easyprograminstaller/downloaded/vivaldi.deb \"https://downloads.vivaldi.com/stable/vivaldi-stable_1.9.818.50-1_amd64.deb\" -q --no-check-certificate --show-progress --progress=dot"
                                        ,"sudo dpkg -i /home/$USER/.config/easyprograminstaller/downloaded/vivaldi.deb"
                                        ,"echo '--CHECKDOWNLOADFOLDER--'"
                                        ,"dpkg -l | grep -o 'ii  vivaldi'"});

    AppList.insert("Opera", {"sudo sh -c 'echo \"deb http://deb.opera.com/opera/ stable non-free\" >> /etc/apt/sources.list.d/opera.list'"
                                        ,"wget http://deb.opera.com/archive.key -q -O - | sudo apt-key add -"
                                        ,"sudo apt update"
                                        ,"sudo apt install opera"
                                        ,"dpkg -l | grep -o 'ii  opera'"});

    AppList.insert("Spotify", {"sudo apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv-keys BBEBDCB318AD50EC6865090613B00F1FD2C19886"
                                        ,"echo deb http://repository.spotify.com stable non-free | sudo tee /etc/apt/sources.list.d/spotify.list"
                                        ,"sudo apt update"
                                        ,"sudo apt install spotify-client"
                                        ,"dpkg -l | grep -o 'ii  spotify'"});

    AppList.insert("VLC Media Player", {"sudo apt install vlc -y"
                                        ,"dpkg -l | grep -o 'ii  vlc'"});

    AppList.insert("GIMP Image Editor", {"sudo apt install gimp -y"
                                        ,"dpkg -l | grep -o 'ii  gimp'"});

    AppList.insert("Pitivi Video Editor", {"sudo apt install pitivi -y"
                                        ,"dpkg -l | grep -o 'ii  pitivi'"});

    AppList.insert("Telegram Desktop", {"wget -O /home/$USER/.config/easyprograminstaller/downloaded/telegram.tar.xz \"https://telegram.org/dl/desktop/linux\" -q --no-check-certificate --show-progress --progress=dot"
                                        ,"cd /home/$USER/.config/easyprograminstaller/downloaded/"
                                        ,"tar xf telegram.tar.xz"
                                        ,"cd Telegram"
                                        ,"sudo cp Telegram /usr/bin/telegram"
                                        ,"telegram"
                                        ,"echo '--CHECKDOWNLOADFOLDER--'"
                                        ,"which 'telegram'"});

    AppList.insert("Skype", {"sudo apt install skype -y"
                                        ,"dpkg -l | grep -o 'ii  skype'"});

    AppList.insert("TeamViewer", {"wget -O /home/$USER/.config/easyprograminstaller/downloaded/teamviewer.deb \"https://download.teamviewer.com/download/teamviewer_i386.deb\" -q --no-check-certificate --show-progress --progress=dot"
                                        ,"sudo dpkg -i /home/$USER/.config/easyprograminstaller/downloaded/teamviewer.deb"
                                        ,"echo '--CHECKDOWNLOADFOLDER--'"
                                        ,"dpkg -l | grep -o 'ii  teamviewer'"});

    AppList.insert("VirtualBox", {"sudo apt install virtualbox -y"
                                        ,"dpkg -l | grep -o 'ii  virtualbox'"});




    // LIST_TOOLS
    AppList.insert("Unity Tweak Tool", {"sudo apt install unity-tweak-tool -y"
                                        ,"dpkg -l | grep -o 'ii  unity-tweak-tool'"});

    AppList.insert("Gnome Tweak Tool", {"sudo apt install gnome-tweak-tool -y"
                                        ,"dpkg -l | grep -o 'ii  gnome-tweak-tool'"});

    AppList.insert("FileZilla", {"sudo apt install filezilla -y"
                                        ,"dpkg -l | grep -o 'ii  filezilla'"});

    AppList.insert("RecordMyDesktop", {"sudo apt install recordmydesktop -y"
                                        ,"dpkg -l | grep -o 'ii  recordmydesktop'"});

    AppList.insert("dconf Editor", {"sudo apt install dconf-editor -y"
                                        ,"dpkg -l | grep -o 'ii  dconf-editor'"});

    AppList.insert("Wine", {"sudo dpkg --add-architecture i386"
                                        ,"wget -nc https://dl.winehq.org/wine-builds/Release.key"
                                        ,"sudo apt-key add Release.key"
                                        ,"sudo apt-add-repository https://dl.winehq.org/wine-builds/ubuntu/"
                                        ,"deb https://dl.winehq.org/wine-builds/debian/ jessie main"
                                        ,"sudo apt update"
                                        ,"sudo apt install --install-recommends winehq-devel -y"
                                        ,"dpkg -l | grep -o 'ii  winehq-devel'"});

    AppList.insert("Cairo Dock", {"sudo apt install cairo-dock -y"
                                        ,"dpkg -l | grep -o 'ii  cairo-dock'"});

    AppList.insert("Docky", {"sudo apt install docky -y"
                                        ,"dpkg -l | grep -o 'ii  docky'"});

    AppList.insert("Plank", {"sudo add-apt-repository ppa:ricotz/docky"
                                        ,"sudo apt update"
                                        ,"sudo apt install plank -y"
                                        ,"dpkg -l | grep -o 'ii  plank'"});



    // LIST_SYSTEM
    AppList.insert("GParted", {"sudo apt install gparted -y"
                                        ,"dpkg -l | grep -o 'ii  gparted'"});

    AppList.insert("Boot Repair", {"sudo add-apt-repository ppa:yannubuntu/boot-repair"
                                        ,"sudo apt update"
                                        ,"sudo apt install boot-repair -y"
                                        ,"dpkg -l | grep -o 'ii  boot-repair'"});


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
    terminal->start((QString)("/bin/sh -c \"mkdir -p /home/$USER/.config/easyprograminstaller/downloaded\""));
    terminal->waitForFinished();
    terminal->close();

    addAppsToList();
    addSignalsSlots();
    configureAppList();
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
