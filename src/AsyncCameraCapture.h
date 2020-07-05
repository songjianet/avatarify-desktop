#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QString>
#include <QCamera>
#include <QVideoProbe>
#include <QImage>
#include <QCameraInfo>
#include "PoorMansProbe.h"

class AsyncCameraCapture : public QObject {
Q_OBJECT
    Q_PROPERTY(QString deviceId READ deviceId WRITE setDeviceId)
    Q_PROPERTY(bool mirror READ mirror WRITE setMirror)
    Q_PROPERTY(bool smartCrop READ smartCrop WRITE setSmartCrop)

public:
    explicit AsyncCameraCapture(QObject *parent = nullptr);

    QString deviceId();

    void setDeviceId(const QString &deviceId);

    bool mirror() const;

    void setMirror(bool mirror);

    bool smartCrop() const;

    void setSmartCrop(bool smartCrop);

    QImage frame();

private slots:

    void setCamera(const QCameraInfo &cameraInfo);

    void processFrame(const QVideoFrame &frame);

private:
    QScopedPointer<QCamera> m_camera;
    QScopedPointer<PoorMansProbe> m_videoprobe;
    QScopedPointer<QCameraViewfinderSettings> m_vfsettings;

    QCameraInfo m_cameraInfo;
    bool m_mirror;
    bool m_smartCrop;
    QImage m_frame;
};

#endif // BACKEND_H
