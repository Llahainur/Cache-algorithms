#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QMessageBox>
#include <QFileDialog>
#include <QRadioButton>
#include <QButtonGroup>
#include <QTimer>
#include <QRandomGenerator>
#include <QVector>


#include "user.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_StartButton_clicked();

    void on_FileButton_clicked();

    void on_StopButton_clicked();

    void updateTime();

private:
    Ui::MainWindow *ui;
    QTimer *tmr;
    int mode=0;
    QRandomGenerator generator;
    QMap<QString, int> MRU;

};
#endif // MAINWINDOW_H
