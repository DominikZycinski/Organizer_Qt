#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include "organizer.h"

namespace Ui {
class Login;
}

class Login : public QMainWindow
{
    Q_OBJECT

public:
    QSqlDatabase mydb;



    bool connOpen(){
        mydb = QSqlDatabase::addDatabase("QSQLITE");
        mydb.setDatabaseName("D:/sqlite3/EmployeeInfo.db");

        if(!mydb.open()){
             qDebug()<<("Database is disconnected");
             return false;
        }
        else if(mydb.open() ){
             qDebug()<<("Database is connected");
            return true;
        }
    }


public:
    explicit Login(QWidget *parent = 0);
    ~Login();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Login *ui;

};

#endif // LOGIN_H
