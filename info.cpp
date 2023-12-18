/*
 * This is just for initializing the info.ui
 */


#include "info.h"
#include "ui_info.h"
#include <QString>
#include <QPixmap>
Info::Info(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Info)
{
    ui->setupUi(this);
}

Info::~Info()
{
    delete ui;

}
