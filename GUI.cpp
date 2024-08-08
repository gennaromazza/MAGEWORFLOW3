#include "GUI.h"
#include "Utils.h"

GUI::GUI(QWidget *parent) : QWidget(parent), worker(new ConversionWorker(this)) {
    mainLayout = new QVBoxLayout(this);
    tabWidget = new QTabWidget(this);

    // Configurazione della scheda di Conversione
    conversionTab = new QWidget(this);
    conversionLayout = new QVBoxLayout(conversionTab);
    startButton = new QPushButton("Start", conversionTab);
    progressBar = new QProgressBar(conversionTab);
    statusLabel = new QLabel("Ready", conversionTab);
    formatComboBox = new QComboBox(conversionTab);
    qualitySpinBox = new QSpinBox(conversionTab);
    resizeCheckBox = new QCheckBox("Resize", conversionTab);
    srcDirLineEdit = new QLineEdit(conversionTab);
    destDirLineEdit = new QLineEdit(conversionTab);

    conversionLayout->addWidget(new QLabel("Origine:", conversionTab));
    conversionLayout->addWidget(srcDirLineEdit);
    conversionLayout->addWidget(new QLabel("Destinazione:", conversionTab));
    conversionLayout->addWidget(destDirLineEdit);
    conversionLayout->addWidget(new QLabel("Formato:", conversionTab));
    conversionLayout->addWidget(formatComboBox);
    conversionLayout->addWidget(new QLabel("Qualità:", conversionTab));
    conversionLayout->addWidget(qualitySpinBox);
    conversionLayout->addWidget(resizeCheckBox);
    conversionLayout->addWidget(startButton);
    conversionLayout->addWidget(progressBar);
    conversionLayout->addWidget(statusLabel);

    tabWidget->addTab(conversionTab, "Conversion");

    connect(startButton, &QPushButton::clicked, this, &GUI::onStartButtonClicked);
    connect(worker, &ConversionWorker::progressUpdated, this, &GUI::onProgressUpdated);
    connect(worker, &ConversionWorker::finished, this, &GUI::onFinished);
    connect(worker, &ConversionWorker::cpuUsageUpdated, this, &GUI::onCpuUsageUpdated);

    // Configurazione della scheda di Ingest
    ingestTab = new QWidget(this);
    ingestLayout = new QVBoxLayout(ingestTab);
    ingestStartButton = new QPushButton("Ingest", ingestTab);
    ingestSrcDirLineEdit = new QLineEdit(ingestTab);
    ingestDestDirLineEdit = new QLineEdit(ingestTab);
    jobTypeComboBox = new QComboBox(ingestTab);
    jobNameLineEdit = new QLineEdit(ingestTab);
    jobDateEdit = new QDateEdit(ingestTab);

    jobTypeComboBox->addItems({"Matrimoni", "Battesimi", "Comunioni", "Shooting"});

    ingestLayout->addWidget(new QLabel("Origine:", ingestTab));
    ingestLayout->addWidget(ingestSrcDirLineEdit);
    ingestLayout->addWidget(new QLabel("Destinazione:", ingestTab));
    ingestLayout->addWidget(ingestDestDirLineEdit);
    ingestLayout->addWidget(new QLabel("Tipologia:", ingestTab));
    ingestLayout->addWidget(jobTypeComboBox);
    ingestLayout->addWidget(new QLabel("Nome del Lavoro:", ingestTab));
    ingestLayout->addWidget(jobNameLineEdit);
    ingestLayout->addWidget(new QLabel("Data del Lavoro:", ingestTab));
    ingestLayout->addWidget(jobDateEdit);
    ingestLayout->addWidget(ingestStartButton);

    tabWidget->addTab(ingestTab, "Ingest");

    connect(ingestStartButton, &QPushButton::clicked, this, &GUI::onIngestStartButtonClicked);

    // Configurazione della scheda di Nuovo Backup
    backupTab = new QWidget(this);
    backupLayout = new QVBoxLayout(backupTab);
    backupStartButton = new QPushButton("Start Backup", backupTab);
    backupSrcDirLineEdit = new QLineEdit(backupTab);
    backupDestDirLineEdit = new QLineEdit(backupTab);
    backupStatusLabel = new QLabel("Ready", backupTab);

    backupLayout->addWidget(new QLabel("Origine:", backupTab));
    backupLayout->addWidget(backupSrcDirLineEdit);
    backupLayout->addWidget(new QLabel("Destinazione:", backupTab));
    backupLayout->addWidget(backupDestDirLineEdit);
    backupLayout->addWidget(backupStartButton);
    backupLayout->addWidget(backupStatusLabel);

    tabWidget->addTab(backupTab, "Nuovo Backup");

    connect(backupStartButton, &QPushButton::clicked, this, &GUI::onBackupStartButtonClicked);

    mainLayout->addWidget(tabWidget);
    setLayout(mainLayout);
}

void GUI::onStartButtonClicked() {
    QString srcDir = srcDirLineEdit->text();
    QString destDir = destDirLineEdit->text();
    int quality = qualitySpinBox->value();
    bool resize = resizeCheckBox->isChecked();
    int maxLength = 0;
    if (resize) {
        bool ok;
        maxLength = QInputDialog::getInt(this, "Dimensione del Bordo Lungo", "Inserisci la dimensione in px:", 800, 1, 10000, 1, &ok);
        if (!ok) {
            return;
        }
    }
    QString actionExisting = "Sovrascrivi"; // Si può aggiungere un widget per questa opzione se necessario
    bool createSubdirs = true; // Si può aggiungere un widget per questa opzione se necessario
    QStringList formats = {"JPEG"}; // Si può aggiungere un widget per questa opzione se necessario

    worker->setup(srcDir, destDir, quality, resize, maxLength, actionExisting, createSubdirs, formats);
    worker->start();
    statusLabel->setText("In esecuzione...");
}

void GUI::onProgressUpdated(int total, int processed, int errors) {
    progressBar->setMaximum(total);
    progressBar->setValue(processed);
    statusLabel->setText(QString("Processed: %1/%2 Errors: %3").arg(processed).arg(total).arg(errors));
}

void GUI::onFinished(const QString &outputDir, int totalFiles, int convertedFiles) {
    statusLabel->setText(QString("Completato: %1 files convertiti su %2").arg(convertedFiles).arg(totalFiles));
}

void GUI::onCpuUsageUpdated(float usage) {
    // Aggiornamento dell'uso della CPU
}

void GUI::onIngestStartButtonClicked() {
    QString srcDir = ingestSrcDirLineEdit->text();
    QString destDir = ingestDestDirLineEdit->text();
    QString jobType = jobTypeComboBox->currentText();
    QString jobName = jobNameLineEdit->text();
    QDate jobDate = jobDateEdit->date();

    QString formattedDate = jobDate.toString("MMddyyyy");
    QString destPath = QString("%1/%2/%3 %4").arg(destDir, jobType, formattedDate, jobType.toUpper() + " " + jobName.toUpper());

    QDir().mkpath(destPath);
    Utils::syncDirectories(srcDir, destPath);
}

void GUI::onBackupStartButtonClicked() {
    QString srcDir = backupSrcDirLineEdit->text();
    QString destDir = backupDestDirLineEdit->text();
    QString status;
    Utils::compareDirectories(srcDir, destDir, status);
    backupStatusLabel->setText(status);
}
