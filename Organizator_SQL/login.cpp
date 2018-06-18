#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    QPixmap pix("C:/Users/Domin/OneDrive/Pulpit/organizer.png");
    ui->label_pic->setPixmap(pix);

//    mydb = QSqlDatabase::addDatabase("QSQLITE");
//    mydb.setDatabaseName("D:/sqlite3/EmployeeInfo.db");

    if(!connOpen()){
        ui->label->setText("Database is disconnected");
    }
    else if(connOpen() ){
        ui->label->setText("Database is connected");
    }

}


Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_clicked()
{
    QString username, password;
    username= ui -> lineEdit_username ->text();
    password= ui -> lineEdit_password ->text();

    if(!connOpen()){
        qDebug()<<"Failed to open the database";
                return;
    }

    connOpen();
    QSqlQuery qry;
    qry.prepare("select * from emplee where username= '"+username +"' and password= '"+password+"'");


    if(qry.exec())  {

        int count=0;
        while(qry.next())
        {
            count++;
        }

        if(count ==1){
            ui->label->setText("zalogowales sie");

            this -> hide();
            Organizer organizer;
            organizer.setModal(true);
            organizer.exec();

        }
        if(count <1){
        ui->label->setText(" nie zalogowales sie");
        }

    }

}
