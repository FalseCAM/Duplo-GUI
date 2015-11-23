#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QProcess>
#include <QDirIterator>
#include <QDir>
#include <QDebug>
#include <QTemporaryFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionQuit_triggered()
{
    this->close();
}

void MainWindow::on_actionAdd_Files_triggered()
{
    QStringList fileNames = QFileDialog::getOpenFileNames(this,
                                                          tr("Select Files"), "", "Source Files (*.c *.cpp *.cc);;Header Files (*.h *.hpp);;Source and Header Files(*.c *.cpp *.cc *.h *.hpp)");
    addFiles(fileNames);
}

void MainWindow::on_actionAdd_Folder_triggered()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                    "",
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);

    QDirIterator it(dir, QStringList() << "*.cpp" << "*.cc" << "*.c" << "*.h" << "*.hpp", QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        ui->fileListWidget->addItem(it.next());
    }

}

void MainWindow::addFiles(QStringList files)
{
    if (!files.isEmpty()) {
        foreach(QString file, files){

            if(QFile().exists(file)){
                ui->fileListWidget->addItem(file);
            }
        }
    }
}

void MainWindow::on_analyzePushButton_clicked()
{
    QTemporaryFile tempInFile("filesXXXX.txt");
    QTemporaryFile tempOutFile("resultXXXXX.txt");

    if(tempInFile.open() && tempOutFile.open())
    {

        QFile fOut(tempInFile.fileName());
        if (fOut.open(QFile::WriteOnly | QFile::Text)) {
            QTextStream ots(&fOut);
            for (int i = 0; i < ui->fileListWidget->count(); ++i)
                ots << ui->fileListWidget->item(i)->text() << "\n";
        } else {
        }
        fOut.close();
        analyze(tempInFile.fileName(), tempOutFile.fileName());
    }
}

void MainWindow::analyze(QString inputFile, QString resultFile)
{
#ifdef Q_OS_UNIX
    QString program = "./duplo";
#else
    QString program = "duplo.exe";
#endif
    QStringList arguments;
    arguments << inputFile << resultFile;

    QProcess process;
    process.start(program, arguments);
    process.waitForFinished(1000*60*60*24);
    ui->resultTextBrowser->setText(process.readAll());
    readResult(resultFile);
    ui->tabWidget->setCurrentIndex(1);
}

void MainWindow::readResult(QString resultFile)
{
    QFile fIn(resultFile);
    if (fIn.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream sIn(&fIn);
        while (!sIn.atEnd())
            ui->resultTextBrowser->append(sIn.readLine());
    } else {
    }
}
