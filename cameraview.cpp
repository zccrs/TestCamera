#include "cameraview.h"
#include <QPainter>
#include <QVideoWidget>
#include <QVideoSurfaceFormat>
#include <QAbstractVideoBuffer>

CameraFormatProxy::CameraFormatProxy(QObject *parent):
    QAbstractVideoSurface(parent)
{
}

QVideoFrame& CameraFormatProxy::currentFrame() const
{
    return const_cast<QVideoFrame&>(m_currentFrame);
}

bool CameraFormatProxy::present(const QVideoFrame &frame)
{
    m_currentFrame = frame;
    emit currentFrameChanged();
    return true;
}

QList<QVideoFrame::PixelFormat> CameraFormatProxy::supportedPixelFormats(QAbstractVideoBuffer::HandleType) const
{
    return QList<QVideoFrame::PixelFormat>()
                     << QVideoFrame::Format_RGB32
                     << QVideoFrame::Format_ARGB32
                     << QVideoFrame::Format_ARGB32_Premultiplied
                     << QVideoFrame::Format_RGB565
                     << QVideoFrame::Format_RGB555;
}

bool CameraFormatProxy::isFormatSupported(const QVideoSurfaceFormat &format) const
{
    return QVideoFrame::imageFormatFromPixelFormat(format.pixelFormat())!=QImage::Format_Invalid;
}


CameraView::CameraView(QWidget *parent) :
    QWidget(parent),
    m_mirroredHorizontal(false),
    m_mirroredVertical(false),
    m_source(NULL),
    m_scale(1.0),
    m_aspectRatioMode(Qt::KeepAspectRatio),
    m_brightness(0),
    m_contrast(0),
    m_hue(0),
    m_saturation(0)
{
    cameraFormatProxy = new CameraFormatProxy(this);
    connect(cameraFormatProxy, SIGNAL(currentFrameChanged()), this, SLOT(repaint()));
}

QCamera* CameraView::source() const
{
    return m_source;
}

bool CameraView::mirroredHorizontal() const
{
    return m_mirroredHorizontal;
}

bool CameraView::mirroredVertical() const
{
    return m_mirroredVertical;
}

void CameraView::paint(const QVideoFrame &frame)
{
    QPainter painter(this);

    QImage image(
                frame.bits(),
                frame.width(),
                frame.height(),
                frame.bytesPerLine(),
                QVideoFrame::imageFormatFromPixelFormat(frame.pixelFormat()));

    painter.drawImage(0, 0, image.mirrored(m_mirroredHorizontal, m_mirroredVertical));
}

qreal CameraView::scale() const
{
    return m_scale;
}

Qt::AspectRatioMode CameraView::aspectRatioMode() const
{
    return m_aspectRatioMode;
}

int CameraView::brightness() const
{
    return m_brightness;
}

int CameraView::contrast() const
{
    return m_contrast;
}

int CameraView::hue() const
{
    return m_hue;
}

int CameraView::saturation() const
{
    return m_saturation;
}

void CameraView::setSource(QCamera *source)
{
    if (m_source == source)
        return;

    m_source = source;
    m_source->setCaptureMode(QCamera::CaptureStillImage);
    m_source->setViewfinder(cameraFormatProxy);

    emit sourceChanged(source);
}

void CameraView::setMirroredHorizontal(bool mirroredHorizontal)
{
    if (m_mirroredHorizontal == mirroredHorizontal)
        return;

    m_mirroredHorizontal = mirroredHorizontal;
    emit mirroredHorizontalChanged(mirroredHorizontal);
}

void CameraView::setMirroredVertical(bool mirroredVertical)
{
    if (m_mirroredVertical == mirroredVertical)
        return;

    m_mirroredVertical = mirroredVertical;
    emit mirroredVerticalChanged(mirroredVertical);
}

void CameraView::setScale(qreal scale)
{
    if (m_scale == scale)
        return;

    m_scale = scale;
    emit scaleChanged(scale);
}

void CameraView::setAspectRatioMode(Qt::AspectRatioMode mode)
{
    m_aspectRatioMode = mode;
}

void CameraView::setBrightness(int brightness)
{
    if(m_brightness == brightness)
        return;
}

void CameraView::setContrast(int contrast)
{
    if(m_contrast == contrast)
        return;
}

void CameraView::setHue(int hue)
{
    if(m_hue == hue)
        return;
}

void CameraView::setSaturation(int saturation)
{
    if(m_saturation == saturation)
        return;
}

void CameraView::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    QVideoFrame &frame = cameraFormatProxy->currentFrame();

    frame.map(QAbstractVideoBuffer::ReadOnly);
    QImage image(
                frame.bits(),
                frame.width(),
                frame.height(),
                QVideoFrame::imageFormatFromPixelFormat(frame.pixelFormat()));
    frame.unmap();

    if(image.isNull())
        return;

    image = image.scaled(size()*m_scale, m_aspectRatioMode, Qt::SmoothTransformation);
    image = image.mirrored(m_mirroredHorizontal, m_mirroredVertical);

    /*QPainterPath path;
    int diameter = qMin(image.width(), image.height());
    path.addEllipse(width()/2.0-diameter/2.0, height()/2.0-diameter/2.0, diameter, diameter);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.setClipPath(path);*/
    painter.drawImage(rect().center() - image.rect().center(), image);
}

