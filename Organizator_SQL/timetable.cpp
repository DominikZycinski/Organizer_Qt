#include "timetable.h"
#include "ui_timetable.h"
#include <QMessageBox>
Timetable::Timetable(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Timetable)
{
    ui->setupUi(this);

    loadTimetable();
    QSqlQueryModel *modal = new QSqlQueryModel();
    Login conn;
    conn.connOpen();
    QSqlQuery *qry = new QSqlQuery(conn.mydb);
    qry->prepare("select surname from kontakty");

    qry->exec();
    modal->setQuery(*qry);
    ui->comboBox2 ->setModel(modal);
}

Timetable::~Timetable()
{
    delete ui;
}

void Timetable::loadTimetable(){
    Login conn;
    QSqlQueryModel *modal = new QSqlQueryModel();

    conn.connOpen();
    QSqlQuery *qry = new QSqlQuery (conn.mydb);

    qry -> prepare("select Uczestnik, Data, Notatki from spotkania");

    qry->exec();
    modal ->setQuery(*qry);
    ui ->tableView_timetable->setModel(modal);

    qDebug() <<(modal->rowCount());
}

void Timetable::on_pb_add_meet2_clicked()
{
//    QDate data;
//    data = QDate::fromString(ui->calendar->selectedDate().toString("dd-MM-yyyy"), "dd-MM-yyyy");
//    ui->lineEdit_date->setText(data.toString());


    Login conn;
    QString  uczestnik, data2, notatki;
    uczestnik= ui -> comboBox2 ->currentText();
    data2= ui -> lineEdit_date2->text();
    notatki= ui -> lineEdit_notes2->text();

    if(!conn.connOpen()){
        qDebug()<<"Failed to open the database";
                return;
    }

    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("insert into spotkania ('Uczestnik_Spotkania', 'Data_Spotkania', Notatki) values ('"+uczestnik+"','"+data2+"','"+notatki+"')");
//     qry.prepare("insert into kontakty(name, surname, phone, mail, company) values ('"+name+"','"+surname+"','"+phone+"','"+mail+"','"+company+"')");
    if(qry.exec())  {
            QMessageBox::critical(this, tr("Edit"), tr("Updated"));
    }
    else{
        QMessageBox::critical(this, tr("error::"), qry.lastError().text());
    }

}

void Timetable::on_pb_update_meet_clicked()
{
    Login conn;
    QString  id, uczestnik, data2, notatki;
    id = ui->lineEdit2_id_timetable ->text();
    uczestnik= ui -> comboBox2 ->currentText();
    data2= ui -> lineEdit_date2->text();
    notatki= ui -> lineEdit_notes2->text();

    if(!conn.connOpen()){
        qDebug()<<"Failed to open the database";
                return;
    }

    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("update spotkania set Uczestnik  ='"+uczestnik+"', Data ='"+data2+"' , Notatki ='"+notatki+"' WHERE Numer = '"+id+"'");
//    qry.prepare("update kontakty set name ='"+name+"', surname='"+surname+"', phone='"+phone+ "', mail='"+mail+"', company ='"+company+"' WHERE ID = '"+id+"'");


    if(qry.exec())  {
            QMessageBox::critical(this, tr("Edit"), tr("Updated"));
    }
    else{
        QMessageBox::critical(this, tr("error::"), qry.lastError().text());
    }
    loadTimetable();

}

void Timetable::on_tableView_timetable_activated(const QModelIndex &index)
{
    QString val = ui->tableView_timetable->model()->data(index).toString();

    Login conn;

    if(!conn.connOpen()){
        qDebug()<<"Failed to open the database";
        return;
    }

    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("select * from spotkania where Uczestnik = '"+val+"' or Data = '"+val+"' or Notatki = '"+val+"' ");

    if(qry.exec()){
        while(qry.next()){
            ui->lineEdit2_id_timetable ->setText(qry.value(0).toString());
            ui->lineEdit_date2 ->setText(qry.value(2).toString());
            ui->lineEdit_notes2 ->setText(qry.value(3).toString());
//            ui->lineEdit_surname->setText(qry.value(2).toString());

        }
    }
    else{
        QMessageBox::critical(this, tr("error::"),qry.lastError().text());
    }

}

void Timetable::on_pb_delete_meet_clicked()
{
    Login conn;
    QString id;
    id = ui ->lineEdit2_id_timetable ->text();


    if(!conn.connOpen()){
        qDebug()<<"Failed to open the database";
                return;
    }

    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("delete from spotkania WHERE Numer = '"+id+"'");


    if(qry.exec())  {
            QMessageBox::critical(this, tr("Delete"), tr("Deleted"));
    }
    else{
        QMessageBox::critical(this, tr("error::"), qry.lastError().text());
    }
    loadTimetable();
}
