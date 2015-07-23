#include "form.h"
#include "ui_form.h"

#include <QCamera>
#include <QCameraInfo>
#include <QCameraViewfinder>
#include <QMediaRecorder>
#include <QMediaMetaData>
#include <QVideoProbe>
#include <QCameraImageCapture>
#include <QDebug>

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);

    camera = new QCamera(QCameraInfo::defaultCamera(), this);
    viewfinder = new CameraView(ui->widget);
    viewfinder->resize(200,200);

    viewfinder->move(ui->widget->width()/2-viewfinder->width()/2, ui->widget->height()/2-viewfinder->height()/2);

    if(camera){
        viewfinder->setSource(camera);
        camera->start();
    }
}

Form::~Form()
{
    camera->stop();
    delete ui;
}

void Form::on_horizontalSlider_valueChanged(int value)
{
    viewfinder->resize(200*(1+value/50.0), 200*(1+value/50.0));
    viewfinder->move(ui->widget->width()/2-viewfinder->width()/2, ui->widget->height()/2-viewfinder->height()/2);
}

void Form::on_pushButton_clicked()
{
    ui->label->setPixmap(viewfinder->grab());
}

void Form::on_pushButton_2_clicked()
{
    viewfinder->setMirroredHorizontal(!viewfinder->mirroredHorizontal());
}
