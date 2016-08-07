#ifndef ADDNEWDIALOG_H
#define ADDNEWDIALOG_H

#include <QDialog>
class QString;

namespace Ui {
class addNewDialog;
}

class addNewDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addNewDialog(QWidget *parent = 0);
    ~addNewDialog();

private:
    Ui::addNewDialog *ui;

signals:
    void getName(QString);

private slots:
    void on_buttonBox_accepted();
    void enableOkButton(QString );


public slots:


};

#endif // ADDNEWDIALOG_H
