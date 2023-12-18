#include "graphicscenemanager.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QImageReader>
#include <QMessageBox>

GraphicSceneManager::GraphicSceneManager(QObject *parent)
    : QObject{parent}
{
    imageScene = new QGraphicsScene(this);
    files.setExtensions(imgExtensions);
}
//these are just for initializing the actions main code is in mainwindow.cpp
QGraphicsScene *GraphicSceneManager::scene()
{
    return imageScene;
}

QStringList GraphicSceneManager::supportedExtensions()
{
    return imgExtensions;
}

void GraphicSceneManager::openImage(const QString &fullpath)
{
    files.openFile(fullpath);
    showImage(fullpath);
}

void GraphicSceneManager::nextImage()
{
    showImage(files.nextFile());
}

void GraphicSceneManager::previousmage()
{
    showImage(files.previousFile());
}

bool GraphicSceneManager::hasNext()
{
    return files.hasNestFile();
}

bool GraphicSceneManager::hasPrevious()
{
    return files.hasPreviousFile();
}

//this is for preventing weird looking images and broken aspect ratios

void GraphicSceneManager::fitInView()
{
    if(imageScene->items().size() && imageScene->views().size())
    {
        auto view = imageScene->views().at(0);
        view->fitInView(imageScene->items().at(0), Qt::KeepAspectRatio);
        view->setSceneRect(imageScene->items().at(0)->boundingRect());

    }
}

//checks if file is supported

bool GraphicSceneManager::isFileSupported(const QString &fullpath)
{
    for(auto ext : imgExtensions)
    {
        ext = ext.remove(0, 1);
        if(fullpath.endsWith(ext, Qt::CaseInsensitive))
        {
            return true;
        }
    }
    return false;
}

//shows the image in graphicsView using pixmaps. yes this is a bit slow but it makes zero problem in terms of performance.

void GraphicSceneManager::showImage(const QString &fullpath)
{
    imageScene->clear();

    QImageReader imgReader(fullpath);
    imgReader.setAutoTransform(true);

    QImage img = imgReader.read();

    if(!img.isNull())
    {
        QPixmap pixmap = QPixmap::fromImage(img);

        imageScene->addPixmap(pixmap);
        imageScene->update();

        emit imageChanged(files.getCurrentFilename());

    }

}







