#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addnewdialog.h"
#include "rolldialog.h"
#include <QLineEdit>
#include <QLabel>
#include <QLayout>
#include <QDebug>
#include <QVector>
#include <QFile>
#include <QTextStream>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QGridLayout* layout = new QGridLayout();
    ui->restGroup->setLayout(layout);  
    this->setFixedSize(this->width(),this->height());
    openFile();
    connect(ui->addBtn,SIGNAL(pressed()),this,SLOT(addDialog()));
    connect(ui->rollBtn,SIGNAL(pressed()),this,SLOT(rollDialog()));
    connect(ui->editBtn,SIGNAL(toggled(bool)),this,SLOT(edit(bool)));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addDialog(){
    qDebug()<<"Enter Add, vector count : " << data.size();
    addNewDialog addDia(this);
    connect(&addDia,SIGNAL(getName(QString)),this,SLOT(addNewData(QString)));
    addDia.exec();
}

void MainWindow::addNewData(QString text){
    createNewQLabel(text);

    if(!saveFile->open(QIODevice::Append| QIODevice::Text)){
        qDebug()<<"Create New Data File ERROR";
        return;
    }
    QTextStream out(saveFile);
    out <<text <<endl;
    saveFile->close();
}
void MainWindow::createNewQLabel(QString text){
    QLabel* newData = new QLabel(text,this);
    data.append(text);
    // qDebug()<< "Data Size : " <<data.size();
    dynamic_cast<QGridLayout*>(ui->restGroup->layout())->addWidget(newData,(data.size()-1)%10,(data.size()-1)/10,Qt::AlignCenter);
}
void MainWindow::openFile(){
    saveFile = new QFile(SAVE_NAME,this);
    if(saveFile->exists()){
        loadData();
    }
    else {
        if (!saveFile->open(QIODevice::WriteOnly| QIODevice::Text)) {
            qDebug()<<"Create New File failed";
        }
        else
            saveFile->close();
    }
}
void MainWindow::loadData(){
    if(saveFile->open(QIODevice::ReadOnly| QIODevice::Text)){
        QTextStream in(saveFile);
        while(!in.atEnd()){
            createNewQLabel(in.readLine());
        }
        saveFile->close();
    }
}


void MainWindow::rollDialog(){
    RollDialog rollDia(this);
    connect(this,SIGNAL(callRoll(QVector<QString>&)),&rollDia,SLOT(roll(QVector<QString>&)));
    emit callRoll(data);
    rollDia.exec();
}

QVector<QString> MainWindow::getData(){
    return data;
}

void MainWindow::edit(bool q){
    if(q){
        /*When Edit Button is pressed*/
        ui->editBtn->setText("Done");
        ui->rollBtn->setEnabled(false);
        qDebug()<<ui->restGroup->layout()->count();

        /*Delete QLabels in restGroup*/
        qDebug() <<"delete " <<deleteAllWidgets(ui->restGroup->layout()) << " QLabels." ;

        /*Add QLineEdit in restGroup*/
        for (int i = 0; i < data.size(); ++i) {
            dynamic_cast<QGridLayout*>(ui->restGroup->layout())->addWidget(new QLineEdit(data[i],ui->restGroup),i%10,i/10,Qt::AlignCenter);
        }

    }
    else{
        /*When Done is pressed*/
        ui->editBtn->setText("Edit...");
        ui->rollBtn->setEnabled(true);

        /*Delete QLineEdits in restGroup and overwrite NEW data to .dat*/
        saveFile->open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text);
        QTextStream out(saveFile);

        for (int i = 0; i < data.size(); ++i) {
            QLayoutItem* child = dynamic_cast<QGridLayout*>(ui->restGroup->layout())->itemAtPosition(i%10,i/10);
            qDebug() << "EDIT(i) : " << i << dynamic_cast<QLineEdit*>(child->widget())->text();
            if (dynamic_cast<QLineEdit*>(child->widget())->text() != data[i])
                data[i] = dynamic_cast<QLineEdit*>(child->widget())->text();
            out <<data[i]<<endl;
        }
           saveFile->close();
     qDebug() <<"delete " <<deleteAllWidgets(ui->restGroup->layout()) << " QLineEdits." ;




        /*Add QLabel back in restGroup*/
        foreach (QString i, data) {
            dynamic_cast<QGridLayout*>(ui->restGroup->layout())->addWidget(new QLabel(i,ui->restGroup),data.indexOf(i)%10,data.indexOf(i)/10,Qt::AlignCenter);
            qDebug() <<i;
        }
        qDebug() << "END";
    }
}

int MainWindow::deleteAllWidgets(QLayout *layout){
    QLayoutItem* child = layout->takeAt(0);
    int count = 0;
    while(child!=NULL){
        child->widget()->hide();
        delete child;
        count++;
        child = layout->takeAt(0);
    }
    return count;
}

