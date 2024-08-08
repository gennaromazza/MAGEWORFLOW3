#ifndef CONVERSION_WORKER_H
#define CONVERSION_WORKER_H

#include <QObject>
#include <QThread>
#include <QString>
#include <QDir>
#include <opencv2/opencv.hpp>
#include <log4cpp/Category.hh>

class ConversionWorker : public QThread {
    Q_OBJECT

public:
    explicit ConversionWorker(QObject *parent = nullptr);
    void setup(const QString &srcDir, const QString &destDir, int quality, bool resize, int maxLength, const QString &actionExisting, bool createSubdirs, const QStringList &formats);

signals:
    void progressUpdated(int total, int processed, int errors);
    void finished(const QString &outputDir, int totalFiles, int convertedFiles);
    void cpuUsageUpdated(float usage);

protected:
    void run() override;

private:
    QString srcDir;
    QString destDir;
    int quality;
    bool resize;
    int maxLength;
    QString actionExisting;
    bool createSubdirs;
    QStringList formats;
    QString outputDir;
    int totalFiles;
    int convertedFiles;
    bool isPaused;
    bool isStopped;

    void syncDirectories(const QString &src, const QString &dest);
    void convertRawToJpeg(const QString &filePath);
    void resizeImage(cv::Mat &image, int maxLength);
    void logDebug(const std::string &message);
    log4cpp::Category &logger;
};

#endif // CONVERSION_WORKER_H
