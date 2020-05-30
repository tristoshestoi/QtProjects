#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QObject>
#include <QDebug>

class Downloader : public QObject
{
    Q_OBJECT
public:
    explicit Downloader(QObject *parent = nullptr);

public slots:
    void downloadImage(QString link);

signals:
    void downloadComplete(QString fileName);
};

#endif // DOWNLOADER_H
