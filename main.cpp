#include "mainwindow.h"

#include "graphicscenemanager.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString path;
    /*
     * i dont know how any of this argument things work.
     * but i know it passes arguments ;~}
    */
    auto arguments = a.arguments();
    if(arguments.size()>1)
    {
        path = arguments[1];
    }

    GraphicSceneManager sceneManager;
    MainWindow w{sceneManager};

    if(!path.isEmpty())
    {
        w.openImage(path);
    }

    w.show();
    return a.exec();
}
