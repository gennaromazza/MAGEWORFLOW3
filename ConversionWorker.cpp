#include "ConversionWorker.h"

ConversionWorker::ConversionWorker(QObject *parent)
    : QThread(parent), logger(log4cpp::Category::getInstance("ConversionWorker")) {}

void ConversionWorker::setup(const QString &srcDir, const QString &destDir, int quality, bool resize, int maxLength, const QString &actionExisting, bool createSubdirs, const QStringList &formats) {
    this->srcDir = srcDir;
    this->destDir = destDir;
    this->quality = quality;
    this->resize = resize;
    this->maxLength = maxLength;
    this->actionExisting = actionExisting;
    this->createSubdirs = createSubdirs;
    this->formats = formats;
}

void ConversionWorker::run() {
    logger.debug("Inizio esecuzione del thread di conversione");
    if (createSubdirs) {
        outputDir = QDir(destDir).filePath("FileConvertiti");
    } else {
        outputDir = QDir(destDir).filePath(QFileInfo(srcDir).fileName());
    }
    QDir().mkpath(outputDir);
    syncDirectories(srcDir, outputDir);
    emit finished(outputDir, totalFiles, convertedFiles);
    logger.debug("Completamento esecuzione del thread di conversione");
}

void ConversionWorker::syncDirectories(const QString &src, const QString &dest) {
    // Implementazione della sincronizzazione delle cartelle
}

void ConversionWorker::convertRawToJpeg(const QString &filePath) {
    // Implementazione della conversione da RAW a JPEG
}

void ConversionWorker::resizeImage(cv::Mat &image, int maxLength) {
    // Implementazione del ridimensionamento dell'immagine
}

void ConversionWorker::logDebug(const std::string &message) {
    logger.debug(message);
}
