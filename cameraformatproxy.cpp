#include "cameraformatproxy.h"
#include <QVideoSurfaceFormat>

CameraFormatProxy::CameraFormatProxy(QObject *parent):
    QAbstractVideoSurface(parent)
{

}

const QVideoFrame& CameraFormatProxy::currentFrame() const
{
    return m_currentFrame;
}

bool CameraFormatProxy::present(const QVideoFrame &frame)
{
    m_currentFrame = frame;
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

