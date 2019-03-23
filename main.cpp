#include "mainwindow.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QStyleFactory>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            w.size(),
            a.desktop()->availableGeometry()
        )
    );
    w.move(w.pos().x(), w.pos().y() - 50);
    w.show();

    // bb10 themes crashes the app!
    if(a.style()->objectName().indexOf("bb10") >= 0) {
        a.setStyle(QStyleFactory::keys()[QStyleFactory::keys().size()-1]);
    }

    return a.exec();
}
