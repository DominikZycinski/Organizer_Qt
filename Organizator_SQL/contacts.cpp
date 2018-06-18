#include "contacts.h"
#include "ui_contacts.h"
#include "login.h"

Contacts::Contacts(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Contacts)
{
    ui->setupUi(this);

    Login conn;
    if(!conn.connOpen()){
        ui->label_connect->setText("Database3 is disconnected");
    }
    else if(conn.connOpen() ){
        ui->label_connect->setText("Database3 is connected");
    }
}

Contacts::~Contacts()
{
    delete ui;
}

void Contacts::on_pb_add_contact_clicked()
{
//    Login conn;
//    QString name, surname, phone, mail, company;
//    name= ui -> lineEdit_name ->text();
//    surname= ui -> lineEdit_surname ->text();
//    phone= ui -> lineEdit_phone ->text();
//    surname= ui -> lineEdit_surname ->text();
//    if(!conn.connOpen()){
//        qDebug()<<"Failed to open the database";
//                return;
//    }

//    connOpen();
//    QSqlQuery qry;
//    qry.prepare("select * from emplee where username= '"+username +"' and password= '"+password+"'");


//    if(qry.exec())  {

//        int count=0;
//        while(qry.next())
//        {
//            count++;
//        }

//        if(count ==1){
//            ui->label->setText("zalogowales sie");

//            this -> hide();
//            Organizer organizer;
//            organizer.setModal(true);
//            organizer.exec();

//        }
//        if(count <1){
//        ui->label->setText(" nie zalogowales sie");
//        }

//    }

}
