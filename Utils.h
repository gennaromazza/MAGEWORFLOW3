#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QDir>

class Utils {
public:
    static void syncDirectories(const QString &src, const QString &dest);
    static void convertRawToJpeg(const QString &filePath);
    static void compareDirectories(const QString &src, const QString &dest, QString &status);
};

#endif // UTILS_H
