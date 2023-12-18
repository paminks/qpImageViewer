#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class GraphicSceneManager;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(GraphicSceneManager& manager, QWidget *parent = nullptr);
    ~MainWindow();

    void openImage(const QString& fullpath);

protected:
    //for recording user input
    void keyPressEvent(QKeyEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;

private slots:
    //to open help and about windows
    void on_actionAbout_qpImage_triggered();

    void on_actionHelp_triggered();

private:
    //for screen buttons
    void onNextBtnClicked();
    void onPreviousBtnClicked();
    //changing the image on screen
    void onImageChanged(const QString& fileName);
    //functions for actions in viewer
    void previousImage();
    void nextImage();
    void fitInView();
    void zoomIn();
    void zoomOut();

    void showOpenDialog();
    void updateButtons();


//initializing window and scene manager
private:
    Ui::MainWindow *ui;

    GraphicSceneManager& sceneManager;
//name of the default window. this will look like [defaultWindowTitle + yourImage.png] on the title of window
    const QString defaultWindowTitle = "qpImageViewer";
};
#endif // MAINWINDOW_H
