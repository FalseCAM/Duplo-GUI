#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionQuit_triggered();

    void on_actionAdd_Files_triggered();

    void on_actionAdd_Folder_triggered();

    void addFiles(QStringList files);

    void on_analyzePushButton_clicked();

    void analyze(QString inputFile, QString resultFile);

    void readResult(QString resultFile);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
