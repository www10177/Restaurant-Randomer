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
    layout = new QGridLayout();
    openFile();
    ui->setupUi(this);
    connect(ui->addBtn,SIGNAL(pressed()),this,SLOT(addDialog()));
    connect(ui->rollBtn,SIGNAL(pressed()),this,SLOT(rollDialog()));
    connect(ui->editBtn,SIGNAL(toggled(bool)),this,SLOT(edit(bool)));
    ui->restGroup->setLayout(layout);

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

    if(!saveFile->open(QIODevice::Append)){
        qDebug()<<"Create New Data File ERROR";
        return;
    }
    QTextStream out(saveFile);
    out <<text <<endl;
    saveFile->close();
}
void MainWindow::createNewQLabel(QString text){
    //QLineEdit* newData = new QLineEdit(text,this);
    QLabel* newData = new QLabel(text,this);
    //  newData->setReadOnly(true);
    newData->setFocusPolicy(Qt::NoFocus);
    newData->setContextMenuPolicy(Qt::PreventContextMenu);
    data.append(text);
    layout->addWidget(newData,(data.size()-1)%10,(data.size()-1)/10,Qt::AlignCenter);
}
void MainWindow::openFile(){
    saveFile = new QFile(SAVE_NAME,this);
    if(saveFile->exists()){
        qDebug() << "loadData;";
        loadData();
    }
    else {
        if (!saveFile->open(QIODevice::WriteOnly)) {
            qDebug()<<"Create New File failed";
        }
        else
            saveFile->close();
    }
}
void MainWindow::loadData(){
    if(saveFile->open(QIODevice::ReadOnly)){
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
        ui->editBtn->setText("Done");
        ui->rollBtn->setEnabled(false);
                qDebug()<<layout->count();
        QLayoutItem* child = layout->itemAt(0);
        delete ui->restGroup->layout();
    }
    else{

        ui->editBtn->setText("Edit...");
        ui->rollBtn->setEnabled(true);

    }



}

