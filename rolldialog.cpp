#include "rolldialog.h"
#include "ui_rolldialog.h"
#include <QVector>
#include <QLabel>
#include <QTime>
#include <QDebug>
#include <QString>

RollDialog::RollDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RollDialog)
{
    ui->setupUi(this);

     this->setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

RollDialog::~RollDialog()
{
    delete ui;
}

void RollDialog::roll(QVector<QString> &data){
    qsrand(QTime::currentTime().msec());
    ui->result->setText(data[qrand()%data.size()]);
}
