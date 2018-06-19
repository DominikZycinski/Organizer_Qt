#include "contacts.h"
#include "ui_contacts.h"
#include "login.h"
#include <QMessageBox>
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
    Login conn;
    QString name, surname, phone, mail, company;
    name= ui -> lineEdit_name ->text();
    surname= ui -> lineEdit_surname ->text();
    phone= ui -> lineEdit_phone ->text();
    mail= ui -> lineEdit_mail ->text();
    company= ui -> lineEdit_company ->text();

    if(!conn.connOpen()){
        qDebug()<<"Failed to open the database";
                return;
    }

    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("insert into kontakty(name, surname, phone, mail, company) values ('"+name+"','"+surname+"','"+phone+"','"+mail+"','"+company+"')");


    if(qry.exec())  {
            QMessageBox::critical(this, tr("Save"), tr("Saved"));
    }
    else{
        QMessageBox::critical(this, tr("error::"), qry.lastError().text());
    }

}

void Contacts::on_pb_update_contact_clicked()
{
    Login conn;
    QString name, surname, phone, mail, company;
    name= ui -> lineEdit_name ->text();
    surname= ui -> lineEdit_surname ->text();
    phone= ui -> lineEdit_phone ->text();
    mail= ui -> lineEdit_mail ->text();
    company= ui -> lineEdit_company ->text();

    if(!conn.connOpen()){
        qDebug()<<"Failed to open the database";
                return;
    }

    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("update kontakty set name ='"+name+"', surname='"+surname+"', phone='"+phone+ "', mail='"+mail+"', company ='"+company+"' WHERE ID = 1");


    if(qry.exec())  {
            QMessageBox::critical(this, tr("Edit"), tr("Updated"));
    }
    else{
        QMessageBox::critical(this, tr("error::"), qry.lastError().text());
    }

}

void Contacts::on_pb_delete_contact_clicked()
{
    Login conn;
    QString name, surname, phone, mail, company;
    name= ui -> lineEdit_name ->text();
    surname= ui -> lineEdit_surname ->text();
    phone= ui -> lineEdit_phone ->text();
    mail= ui -> lineEdit_mail ->text();
    company= ui -> lineEdit_company ->text();

    if(!conn.connOpen()){
        qDebug()<<"Failed to open the database";
                return;
    }

    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("delete from kontakty WHERE ID = 3");


    if(qry.exec())  {
            QMessageBox::critical(this, tr("Delete"), tr("Deleted"));
    }
    else{
        QMessageBox::critical(this, tr("error::"), qry.lastError().text());
    }
}

void Contacts::on_pb_load_contact_clicked()
{
    Login conn;
    QSqlQueryModel *modal = new QSqlQueryModel();

    conn.connOpen();
    QSqlQuery *qry = new QSqlQuery (conn.mydb);

    qry -> prepare("select * from kontakty");

    qry->exec();
    modal ->setQuery(*qry);
    ui ->tableView->setModel(modal);

    qDebug() <<(modal->rowCount());

}
