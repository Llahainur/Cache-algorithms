#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QButtonGroup Block1;
    Block1.addButton(ui->radioButton,   0);
    Block1.addButton(ui->radioButton_2, 1);
    ui->radioButton->setChecked (0);

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
    if(ui->radioButton->isChecked())
    {

    }
    else if(ui->radioButton_2->isChecked())
    {

    }
    else
    {
        QMessageBox::information(0, "error", "Выберите режим");
    }


}

