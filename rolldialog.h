#ifndef ROLLDIALOG_H
#define ROLLDIALOG_H

#include <QDialog>

class QVector<class T>;
class QLabel;

namespace Ui {
class RollDialog;
}

class RollDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RollDialog(QWidget *parent = 0);
    ~RollDialog();

private:
    Ui::RollDialog *ui;
public slots:
    void roll(QVector<QString>&);

};

#endif // ROLLDIALOG_H
