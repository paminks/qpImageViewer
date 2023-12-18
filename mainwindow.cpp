#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graphicscenemanager.h"
#include "info.h"
#include "help.h"

#include <QFileDialog>
#include <QKeyEvent>
#include <QWheelEvent>
#include <QDropEvent>
#include <QMimeData>

MainWindow::MainWindow(GraphicSceneManager& manager, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow)
    , sceneManager(manager)
{
    ui->setupUi(this);
    setWindowTitle(defaultWindowTitle);
    ui->graphicsView->setScene(sceneManager.scene());
    //connects buttons to their functions
    connect(ui->nextBtn, &QPushButton::clicked, this, &MainWindow::onNextBtnClicked);
    connect(ui->prevBtn, &QPushButton::clicked, this, &MainWindow::onPreviousBtnClicked);
    //connects graphicsView to its function
    connect(&sceneManager, &GraphicSceneManager::imageChanged, this, &MainWindow::onImageChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openImage(const QString &fullpath)
{
    //oppens the file if its supported
    if(sceneManager.isFileSupported(fullpath))
    {
        sceneManager.openImage(fullpath);
        fitInView();

    }
    updateButtons();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    //connects keys to next or prev functions
    switch(event->key())
    {
    case Qt::Key_Left:
        previousImage();
        break;
    case Qt::Key_Right:
        nextImage();
        break;
    case Qt::Key_O:
        if(event->modifiers() & Qt::ControlModifier)
            showOpenDialog();
        break;
    default:
        QWidget::keyPressEvent(event);

    }
}

void MainWindow::wheelEvent(QWheelEvent *event)
{
    //zooms in and out ;~}
    if(event->angleDelta().y()>0)
    {
        zoomIn();
    }else
    {
        zoomOut();
    }
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    //resets the zoom
    if(event->button() == Qt::LeftButton)
        fitInView();
    QWidget::mouseDoubleClickEvent(event);
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    //function for drag
    auto mimeData = event->mimeData();
    if(mimeData->hasUrls())
    {
        auto urls = mimeData->urls();
        if(sceneManager.isFileSupported(urls[0].toLocalFile()))
        {
            event->acceptProposedAction();
        }
    }
}

void MainWindow::dropEvent(QDropEvent *event)
{
    //function for drop
    auto urls = event->mimeData()->urls();
    if(urls.size())
    {
        openImage(urls[0].toLocalFile());
    }
}

void MainWindow::onNextBtnClicked()
{
    //calls next Image
    nextImage();
}

void MainWindow::onPreviousBtnClicked()
{
    //calls previous Image
    previousImage();
}

void MainWindow::onImageChanged(const QString &fileName)
{
    //changes the window title based on current file
    setWindowTitle(QString("%0 - \"%1\"").arg(defaultWindowTitle).arg(fileName));
}

void MainWindow::previousImage()
{
    //opens previous image
    if(sceneManager.hasPrevious())
    {
        sceneManager.previousmage();
        fitInView();
    }
    updateButtons();

}

void MainWindow::nextImage()
{
    //opens next image
    if(sceneManager.hasNext())
    {
        sceneManager.nextImage();
        fitInView();
    }
    updateButtons();
}

void MainWindow::fitInView()
{
    //resets zoom
    sceneManager.fitInView();
}

void MainWindow::zoomIn()
{
    //zooms in
    ui->graphicsView->scale(1.1, 1.1);
}

void MainWindow::zoomOut()
{
    //zoooooms out
    ui->graphicsView->scale(0.9, 0.9);
}

void MainWindow::showOpenDialog()
{
    //opens the file browser
    QString imageExtensions = QString("Images (%0)").arg(sceneManager.supportedExtensions().join(" "));

    QString path = QFileDialog::getOpenFileName(this, "Open image", "", imageExtensions);

    if(path.size())
        openImage(path);
}

void MainWindow::updateButtons()
{
    //updates button based on if there is available next and prev files
    ui->prevBtn->setEnabled(sceneManager.hasPrevious());
    ui->nextBtn->setEnabled(sceneManager.hasNext());
}


void MainWindow::on_actionAbout_qpImage_triggered()
{
    //opens the Info window
    Info info;
    info.setModal(true);
    info.exec();

}


void MainWindow::on_actionHelp_triggered()
{
    //opens the Help window
    help help;
    help.setModal(true);
    help.exec();

}

