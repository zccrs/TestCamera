#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QVideoFrame>
#include "cameraview.h"

namespace Ui {
class Form;
}

class QCamera;
class QCameraViewfinder;

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = 0);
    ~Form();

private slots:
    void on_horizontalSlider_valueChanged(int value);

    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::Form *ui;
    QCamera *camera;
    CameraView *viewfinder;
};

#endif // FORM_H
