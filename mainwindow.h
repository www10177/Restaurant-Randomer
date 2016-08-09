#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#define SAVE_NAME "./restaurant list.dat"
class addNewDialog;
class QVector<class T>;
//class QLineEdit;
class QLabel;
class QGridLayout;
class QFile;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QVector<QString> getData();

private:
    /*Variables*/
    Ui::MainWindow *ui;
    QVector<QString> data;
    QFile* saveFile;

    /*funtions*/
    void openFile();
    void loadData();
    void createNewQLabel(QString);
    int deleteAllWidgets(QLayout*); // return how many widgets deleted

signals:
    void callRoll( QVector<QString>& );


private slots:
   void addDialog();
   /*show OPEN dialog and add QLabel* to vector*/
   void rollDialog();
   /*show ROLL dialog */
   void addNewData(QString);
   /*add new QLabel to vector and show in restgroup*/
   void edit(bool);
   /*delete layout and recreate new layout with QTextEdit*/
};

#endif // MAINWINDOW_H
