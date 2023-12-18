#ifndef GRAPHICSCENEMANAGER_H
#define GRAPHICSCENEMANAGER_H

#include <QObject>
#include <files.h>

class QGraphicsScene;

class GraphicSceneManager : public QObject
{
    Q_OBJECT
public:
    explicit GraphicSceneManager(QObject *parent = nullptr);
    //initializes scene and file extensions
    QGraphicsScene* scene();
    QStringList supportedExtensions();
    void openImage(const QString& fullpath);
    //actions in viewer
    void nextImage();
    void previousmage();
    bool hasNext();
    bool hasPrevious();

    void fitInView();
    bool isFileSupported(const QString& fullpath);


signals:
    void imageChanged(const QString& fileName);

private:
    void showImage(const QString& fullpath);

private:
    Files files;
    QGraphicsScene* imageScene = nullptr;
    const QStringList imgExtensions = {"*.png", "*.bmp", "*.jpg", "*.jpeg", "*.webp"};

};

#endif // GRAPHICSCENEMANAGER_H
