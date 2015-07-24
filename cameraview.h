/*
 *CameraView类功能类似于QVideoWidget，通过setSource设置一个QCamera*对象，CameraView负责将摄像头的每一帧绘制出来。
 * 比着QVideoWidget增加了数码变焦和图像翻转的功能。数码变焦是通过调用setScale改变视频帧绘制时的大小来模拟实现
 * 调用setMirroredHorizontal设置是否开启水平翻转，调用setMirroredVertical设置是否开启竖直翻转
 * CameraFormatProxy类继承于QAbstractVideoSurface，作用是：QCamera对象会调用它的present方法来传输它的每一帧。
*/


#ifndef CAMERAVIEW_H
#define CAMERAVIEW_H

#include <QWidget>
#include <QCamera>

#include <QAbstractVideoSurface>

class CameraView;

class CameraFormatProxy : public QAbstractVideoSurface
{
    Q_OBJECT

public:
    CameraFormatProxy(QObject *parent);
    QVideoFrame& currentFrame() const;
protected:
    bool present(const QVideoFrame &frame);
    QList<QVideoFrame::PixelFormat> supportedPixelFormats(
                QAbstractVideoBuffer::HandleType handleType = QAbstractVideoBuffer::NoHandle) const;
    bool isFormatSupported(const QVideoSurfaceFormat &format) const;
private:
    QVideoFrame m_currentFrame;

Q_SIGNALS:
    void currentFrameChanged();
};

class CameraView : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QCamera* source READ source WRITE setSource NOTIFY sourceChanged)
    //设置要绘制的摄像头对象
    Q_PROPERTY(bool mirroredHorizontal READ mirroredHorizontal WRITE setMirroredHorizontal NOTIFY mirroredHorizontalChanged)
    //是否开启水平翻转
    Q_PROPERTY(bool mirroredVertical READ mirroredVertical WRITE setMirroredVertical NOTIFY mirroredVerticalChanged)
    //是否开启竖直翻转
    Q_PROPERTY(qreal scale READ scale WRITE setScale NOTIFY scaleChanged)
    //视频帧大小=scale*窗口大小，但是超出窗口外的图像并不绘制，所以当scale>1的时候视频图像会被裁剪，以此来模拟变焦
    Q_PROPERTY(Qt::AspectRatioMode aspectRatioMode READ aspectRatioMode WRITE setAspectRatioMode)
    //视频图像适应窗口大小时的模式，具体见Qt文档
    Q_PROPERTY(int brightness READ brightness WRITE setBrightness NOTIFY brightnessChanged)
    //视频亮度调节（待实现）
    Q_PROPERTY(int contrast READ contrast WRITE setContrast NOTIFY contrastChanged)
    //视频对比度调节（待实现）
    Q_PROPERTY(int hue READ hue WRITE setHue NOTIFY hueChanged)
    //视频色调调节（待实现）
    Q_PROPERTY(int saturation READ saturation WRITE setSaturation NOTIFY saturationChanged)
    //视频饱和度调节（待实现）
    Q_PROPERTY(QRect frameRect READ frameRect WRITE setFrameRect NOTIFY frameRectChanged)
    //视频帧在窗口中被绘制的矩形区域（窗口内的可视部分）

public:
    explicit CameraView(QWidget *parent = 0);

    QCamera* source() const;
    bool mirroredHorizontal() const;
    bool mirroredVertical() const;
    void paint(const QVideoFrame& frame);
    qreal scale() const;
    Qt::AspectRatioMode aspectRatioMode() const;

    int brightness() const;
    int contrast() const;
    int hue() const;
    int saturation() const;

    QRect frameRect() const;

    const QVideoFrame* currentFrame() const;
    //返回当前帧
    QPixmap capture();
    //获取视频截图
Q_SIGNALS:
    void sourceChanged(QCamera *source);
    void mirroredHorizontalChanged(bool mirroredHorizontal);
    void mirroredVerticalChanged(bool mirroredVertical);
    void scaleChanged(qreal scale);
    void brightnessChanged(int brightness);
    void contrastChanged(int contrast);
    void hueChanged(int hue);
    void saturationChanged(int saturation);

    void frameRectChanged(QRect frameSize);

public Q_SLOTS:
    void setSource(QCamera *source);
    void setMirroredHorizontal(bool mirroredHorizontal);
    void setMirroredVertical(bool mirroredVertical);

    void setScale(qreal scale);
    void setAspectRatioMode(Qt::AspectRatioMode mode);
    void setBrightness(int brightness);
    void setContrast(int contrast);
    void setHue(int hue);
    void setSaturation(int saturation);
    void setFrameRect(QRect frameRect);

protected:
    void paintEvent(QPaintEvent *event);

private:
    QCamera *m_source;
    CameraFormatProxy *cameraFormatProxy;
    bool m_mirroredHorizontal;
    bool m_mirroredVertical;
    qreal m_scale;
    Qt::AspectRatioMode m_aspectRatioMode;
    int m_brightness;
    int m_contrast;
    int m_hue;
    int m_saturation;
    QRect m_frameRect;
};

#endif // CAMERAVIEW_H
