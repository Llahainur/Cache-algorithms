#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QButtonGroup Block1;
    Block1.addButton(ui->radioButton_FIFO,   0);
    Block1.addButton(ui->radioButton_MRU, 1);
    ui->radioButton_FIFO->setChecked (0);



}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_FileButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Выберите файл"));
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }
    QTextStream in(&file);

    while(!in.atEnd()) {
        QString line = in.readLine();
        ui->FileWidget->addItem(line);
    }
    file.close();

}


void MainWindow::on_StartButton_clicked()
{
    this->user.cache=ui->CacheWidget;
    this->user.file=ui->FileWidget;

    int mode;
    if(ui->radioButton_FIFO->isChecked())
    {
        mode=0;
    }
    else if(ui->radioButton_MRU->isChecked())
    {
        mode=1;
    }
    else
    {
        QMessageBox::information(0, "error", "Выберите режим");
        return;
    }
    this->user.run(mode);
}


void MainWindow::on_StopButton_clicked()
{
    this->user.terminate();
    this->user.deleteLater();

}

