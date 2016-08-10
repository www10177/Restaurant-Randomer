#include "addnewdialog.h"
#include "ui_addnewdialog.h"
#include <QDebug>
#include <QDialogButtonBox>
#include <QPushButton>


addNewDialog::addNewDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addNewDialog)
{
    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    this->setFixedSize(this->width(),this->height());
    this->setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    connect(ui->nameCol,SIGNAL(textChanged(QString)),this,SLOT(enableOkButton(QString)));


}

addNewDialog::~addNewDialog()
{
    delete ui;
}

void addNewDialog::on_buttonBox_accepted()
{
    // qDebug()<<"Emit SIGNAL"<<this->ui->nameCol->text();
    emit getName(this->ui->nameCol->text())   ;
}


void addNewDialog::enableOkButton(QString text){
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(!text.isEmpty());
}

