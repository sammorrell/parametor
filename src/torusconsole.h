#ifndef TORUSCONSOLE_H
#define TORUSCONSOLE_H

#include <QWidget>
#include "qprocess.h"
#include <QDir>
#include <QDebug>
#include <QCloseEvent>
#include <QMessageBox>
#include <QFileSystemWatcher>
#include <QRegularExpression>

namespace Ui {
class torusconsole;
}

class torusconsole : public QWidget
{
    Q_OBJECT
    
public:
    enum RunModes {
        DefaultRunMode,
        CheckRunMode
    };

    explicit torusconsole(QWidget *parent = 0, QString torusPath = "", QString workingPath = "", bool writeToLog = true, RunModes RunMode = torusconsole::DefaultRunMode, QStringList expectedFiles = QStringList());
    ~torusconsole();
    
private:
    Ui::torusconsole *ui;
    QProcess *proc;
    bool isRunning;
    bool writeToLog;
    QFile *logFile;
    QTextStream *logFileOut;
    void closeEvent(QCloseEvent *event);
    int noExpectedFiles;

    //Progress Bar Properties
    QFileSystemWatcher *update;
    QString workingDirectory;
    QStringList expectedFiles;
    QStringList completeFiles;
    QString getInternalBuild();

private slots:
    void slotDataOnStdout();
    void slotProcessFinish();
    void slotProcessStart();
    void slotProcessError();
    void slotFileUpdate(QString dir);
    void on_btn_closeProcess_clicked();
};

#endif // TORUSCONSOLE_H
