#ifndef GUI_H
#define GUI_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QFileDialog>
#include <QProgressBar>
#include <QLabel>
#include <QComboBox>
#include <QSpinBox>
#include <QMessageBox>
#include <QCheckBox>
#include <QInputDialog>
#include <QTabWidget>
#include <QLineEdit>
#include <QDateEdit>
#include "ConversionWorker.h"

class GUI : public QWidget {
    Q_OBJECT

public:
    explicit GUI(QWidget *parent = nullptr);

private slots:
    void onStartButtonClicked();
    void onProgressUpdated(int total, int processed, int errors);
    void onFinished(const QString &outputDir, int totalFiles, int convertedFiles);
    void onCpuUsageUpdated(float usage);

    // Nuovi slot per la funzionalità Ingest
    void onIngestStartButtonClicked();
    // Nuovi slot per la funzionalità Nuovo Backup
    void onBackupStartButtonClicked();

private:
    QVBoxLayout *mainLayout;
    QTabWidget *tabWidget;

    // Scheda di Conversione
    QWidget *conversionTab;
    QVBoxLayout *conversionLayout;
    QPushButton *startButton;
    QProgressBar *progressBar;
    QLabel *statusLabel;
    QComboBox *formatComboBox;
    QSpinBox *qualitySpinBox;
    QCheckBox *resizeCheckBox;
    QLineEdit *srcDirLineEdit;
    QLineEdit *destDirLineEdit;

    // Scheda di Ingest
    QWidget *ingestTab;
    QVBoxLayout *ingestLayout;
    QPushButton *ingestStartButton;
    QLineEdit *ingestSrcDirLineEdit;
    QLineEdit *ingestDestDirLineEdit;
    QComboBox *jobTypeComboBox;
    QLineEdit *jobNameLineEdit;
    QDateEdit *jobDateEdit;

    // Scheda di Nuovo Backup
    QWidget *backupTab;
    QVBoxLayout *backupLayout;
    QPushButton *backupStartButton;
    QLineEdit *backupSrcDirLineEdit;
    QLineEdit *backupDestDirLineEdit;
    QLabel *backupStatusLabel;

    ConversionWorker *worker;
};

#endif // GUI_H
