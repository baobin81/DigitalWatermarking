#include "creation.h"
#include "ui_creation.h"
#include "makewm.h"
#include "menu.h"
#include "validation.h"
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>

creation::creation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::creation)
{
    ui->setupUi(this);
    QIcon icon;
    icon.addFile(":/resources/img/create.png");
    setWindowTitle("Creation");
    setWindowIcon(icon);
}

creation::~creation()
{
    delete ui;
}

void creation::on_createWM_clicked()
{
    makeWM makeW;
    makeW.setModal(true);
    makeW.exec();
}

void creation::on_browseImage_clicked()
{
    QString imgPath = QFileDialog::getOpenFileName(this, "Open image", "C://", "Images (*.jpg)"); //добавить еще расширения при необходимости
    ui->pathImage->setText(imgPath);
}

void creation::on_browseMark_clicked()
{
    QString markPath = QFileDialog::getOpenFileName(this, "Open watermark", "C://", "Signature (*.sig)");
    ui->pathMark->setText(markPath);
}

void creation::on_browseNewImage_clicked()
{
    QDir savePath = QFileDialog::getExistingDirectory(this, "Choose directory for new image", "C://", QFileDialog::ShowDirsOnly);
    ui->pathNewImage->setText(savePath.absolutePath());
}

void creation::on_ok_clicked()
{
    QString imgPath = ui->pathImage->text();
    QString markPath = ui->pathMark->text();
    QString savePath = ui->pathNewImage->text();

    if(imgPath != "" && markPath != "" && savePath != "")
    {
        //
        // добавления водяного знака тут
        // необходимые параметры: imgPath, markPath, savePath
        //
        QMessageBox::about(this, "Result", "Watermark has been added!");
    }
    else
    {
        QMessageBox::warning(this, "Result", "Specify all parameters, please!");
    }
}

void creation::on_cancel_clicked()
{
    close();
}