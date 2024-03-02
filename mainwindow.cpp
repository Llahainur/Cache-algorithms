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

    tmr = new QTimer();
    tmr->setInterval(500);
    connect(tmr, SIGNAL(timeout()), this, SLOT(updateTime()));

    ui->spinBox->setValue(4);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_FileButton_clicked()
{
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this, tr("Выберите файл"));
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
    if(ui->radioButton_FIFO->isChecked())
    {
        mode=1;
    }
    else if(ui->radioButton_MRU->isChecked())
    {
        mode=2;
    }
    else
    {
        QMessageBox::information(0, "error", "Выберите режим");
        return;
    }
    tmr->start();
}


void MainWindow::on_StopButton_clicked()
{
    tmr->stop();
    ui->CacheWidget->clear();
}

void MainWindow::updateTime()
{
    int cache_size = ui->CacheWidget->count();
    int file_size = ui->FileWidget->count();
    int random_value = generator.generate() % file_size;
    int cache_max_size = ui->spinBox->value();

    int flag=1;

    for(int i=0;i<cache_size;i++)
    {
        if(ui->CacheWidget->item(i)->text()==ui->FileWidget->item(random_value)->text())
        {
            flag=0;
        }
    }
    if(flag)
    {
        ui->CacheWidget->addItem(ui->FileWidget->item(random_value)->text());
    }

    if(mode==1)                  //FIFO
    {
        if(cache_size>=cache_max_size)
        {
            qDebug()<< ui->CacheWidget->takeItem(0)->text() <<"delete";
        }

    }
    else if(mode==2)             //MRU
    {
        if(!MRU.contains(ui->FileWidget->item(random_value)->text()))
        {
            MRU.insert(ui->FileWidget->item(random_value)->text(),0);
            qDebug()<<ui->FileWidget->item(random_value)->text();
        }
        else
        {
            MRU[ui->FileWidget->item(random_value)->text()]++;
            qDebug()<<ui->FileWidget->item(random_value)->text()<<MRU[ui->FileWidget->item(random_value)->text()]++;
        }

        if(cache_size>=cache_max_size)
        {
            int min_freq = MRU[ui->CacheWidget->item(0)->text()];
            int index_to_delete=0;
            qDebug()<<"freq"<<min_freq;

            for(int i=0;i<cache_size;i++)
            {
                if(min_freq<MRU[ui->CacheWidget->item(i)->text()])
                {
                    min_freq=MRU[ui->CacheWidget->item(i)->text()];
                    qDebug()<<"freq"<<min_freq<<"item"<<ui->CacheWidget->item(i)->text();
                    index_to_delete=i;
                }
            }
            qDebug()<<"freq"<<min_freq;
            qDebug()<< ui->CacheWidget->takeItem(index_to_delete)->text()<<"delete";
        }
    }
}
