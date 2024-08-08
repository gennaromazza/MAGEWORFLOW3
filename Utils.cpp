#include "Utils.h"
#include <QFile>
#include <QFileInfo>
#include <QDebug>

void Utils::syncDirectories(const QString &src, const QString &dest) {
    QDir srcDir(src);
    QDir destDir(dest);

    if (!srcDir.exists()) {
        qWarning() << "Source directory does not exist: " << src;
        return;
    }

    if (!destDir.exists()) {
        destDir.mkpath(dest);
    }

    QFileInfoList srcFileInfoList = srcDir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot);
    for (const QFileInfo &fileInfo : srcFileInfoList) {
        QString srcFilePath = fileInfo.absoluteFilePath();
        QString destFilePath = destDir.filePath(fileInfo.fileName());
        QFile::copy(srcFilePath, destFilePath);
    }

    QFileInfoList srcDirInfoList = srcDir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
    for (const QFileInfo &dirInfo : srcDirInfoList) {
        QString srcSubDirPath = dirInfo.absoluteFilePath();
        QString destSubDirPath = destDir.filePath(dirInfo.fileName());
        syncDirectories(srcSubDirPath, destSubDirPath);
    }
}

void Utils::convertRawToJpeg(const QString &filePath) {
    // Implementazione della conversione da RAW a JPEG
}

void Utils::compareDirectories(const QString &src, const QString &dest, QString &status) {
    QDir srcDir(src);
    QDir destDir(dest);

    if (!srcDir.exists() || !destDir.exists()) {
        status = "One or both directories do not exist.";
        return;
    }

    QStringList srcEntries = srcDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    QStringList destEntries = destDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);

    QStringList missingInDest;
    QStringList missingInSrc;

    for (const QString &entry : srcEntries) {
        if (!destEntries.contains(entry)) {
            missingInDest << entry;
        }
    }

    for (const QString &entry : destEntries) {
        if (!srcEntries.contains(entry)) {
            missingInSrc << entry;
        }
    }

    status = "Missing in Destination:\n" + missingInDest.join("\n") + "\n\nMissing in Source:\n" + missingInSrc.join("\n");
}
