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


    QSqlQueryModel *modal = new QSqlQueryModel();

    conn.connOpen();
    QSqlQuery *qry = new QSqlQuery (conn.mydb);

    qry -> prepare("select name, surname, phone, mail, company from kontakty");

    qry->exec();
    modal ->setQuery(*qry);
    ui ->tableView->setModel(modal);

    qDebug() <<(modal->rowCount());

}

void Contacts:: load_contacts(){
    Login conn;
    QSqlQueryModel *modal = new QSqlQueryModel();

    conn.connOpen();
    QSqlQuery *qry = new QSqlQuery (conn.mydb);

    qry -> prepare("select name, surname, phone, mail, company from kontakty");

    qry->exec();
    modal ->setQuery(*qry);
    ui ->tableView->setModel(modal);

    qDebug() <<(modal->rowCount());
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

    load_contacts();

}

void Contacts::on_pb_update_contact_clicked()
{
    Login conn;
    QString id, name, surname, phone, mail, company;
    name= ui -> lineEdit_name ->text();
    surname= ui -> lineEdit_surname ->text();
    phone= ui -> lineEdit_phone ->text();
    mail= ui -> lineEdit_mail ->text();
    company= ui -> lineEdit_company ->text();
    id = ui ->lineEdit_id ->text();

    if(!conn.connOpen()){
        qDebug()<<"Failed to open the database";
                return;
    }

    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("update kontakty set name ='"+name+"', surname='"+surname+"', phone='"+phone+ "', mail='"+mail+"', company ='"+company+"' WHERE ID = '"+id+"'");


    if(qry.exec())  {
            QMessageBox::critical(this, tr("Edit"), tr("Updated"));
    }
    else{
        QMessageBox::critical(this, tr("error::"), qry.lastError().text());
    }
    load_contacts();

}

void Contacts::on_pb_delete_contact_clicked()
{
    Login conn;
    QString id, name, surname, phone, mail, company;
    id = ui ->lineEdit_id ->text();
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
    qry.prepare("delete from kontakty WHERE ID = '"+id+"'");


    if(qry.exec())  {
            QMessageBox::critical(this, tr("Delete"), tr("Deleted"));
    }
    else{
        QMessageBox::critical(this, tr("error::"), qry.lastError().text());
    }
    load_contacts();
}


void Contacts::on_pb_sort_name_clicked()
{
    Login conn;
    QSqlQueryModel *modal = new QSqlQueryModel();

    conn.connOpen();
    QSqlQuery *qry = new QSqlQuery (conn.mydb);

    qry -> prepare("select * from kontakty order by name");

    qry->exec();
    modal ->setQuery(*qry);
    ui ->tableView->setModel(modal);

    qDebug() <<(modal->rowCount());
}

void Contacts::on_pb_sort_surname_clicked()
{
    Login conn;
    QSqlQueryModel *modal = new QSqlQueryModel();

    conn.connOpen();
    QSqlQuery *qry = new QSqlQuery (conn.mydb);

    qry -> prepare("select * from kontakty order by surname");

    qry->exec();
    modal ->setQuery(*qry);
    ui ->tableView->setModel(modal);

    qDebug() <<(modal->rowCount());
}

void Contacts::on_pb_sort_company_clicked()
{
    Login conn;
    QSqlQueryModel *modal = new QSqlQueryModel();

    conn.connOpen();
    QSqlQuery *qry = new QSqlQuery (conn.mydb);

    qry -> prepare("select * from kontakty order by company");

    qry->exec();
    modal ->setQuery(*qry);
    ui ->tableView->setModel(modal);

    qDebug() <<(modal->rowCount());
}

//void Contacts::on_pb_load_listview_clicked()
//{
//    Login conn;
//    QSqlQueryModel *modal = new QSqlQueryModel();

//    conn.connOpen();
//    QSqlQuery *qry = new QSqlQuery (conn.mydb);

//    qry -> prepare("select id from kontakty");

//    qry->exec();
//    modal ->setQuery(*qry);
//    ui ->listView->setModel(modal);

//    qDebug() <<(modal->rowCount());
//}

void Contacts::on_tableView_activated(const QModelIndex &index)
{
    QString val = ui->tableView->model()->data(index).toString();

    Login conn;

    if(!conn.connOpen()){
        qDebug()<<"Failed to open the database";
        return;
    }

    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("select * from kontakty where id  = '"+val+"' or name ='"+val+"' or surname='"+val+"' or phone = '"+val+"' or mail = '"+val+"' or company = '"+val+"' ");

    if(qry.exec()){
        while(qry.next()){
            ui->lineEdit_id ->setText(qry.value(0).toString());
            ui->lineEdit_name ->setText(qry.value(1).toString());
            ui->lineEdit_surname->setText(qry.value(2).toString());
            ui->lineEdit_phone ->setText(qry.value(3).toString());
            ui->lineEdit_mail->setText(qry.value(4).toString());
            ui->lineEdit_company->setText(qry.value(5).toString());
        }
    }
    else{
        QMessageBox::critical(this, tr("error::"),qry.lastError().text());
    }

}
