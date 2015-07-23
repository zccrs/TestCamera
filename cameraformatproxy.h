#ifndef CAMERAFORMATPROXY_H
#define CAMERAFORMATPROXY_H

#include <QAbstractVideoSurface>

class CameraFormatProxy : public QAbstractVideoSurface
{
public:
    CameraFormatProxy(QObject *parent = 0);
    const QVideoFrame& currentFrame() const;
protected:
    bool present(const QVideoFrame &frame);
    QList<QVideoFrame::PixelFormat> supportedPixelFormats(
                QAbstractVideoBuffer::HandleType handleType = QAbstractVideoBuffer::NoHandle) const;
    bool isFormatSupported(const QVideoSurfaceFormat &format) const;
private:
    QVideoFrame m_currentFrame;
};

#endif // CAMERAFORMATPROXY_H
