#include "organizer.h"
#include "ui_organizer.h"
#include "login.h"
#include <QMessageBox>
Organizer::Organizer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Organizer)
{
    ui->setupUi(this);

    Login conn;
    if(!conn.connOpen()){
        ui->label_sec_status->setText("Database2 is disconnected");
    }
    else if(conn.connOpen() ){
        ui->label_sec_status->setText("Database2 is connected");
    }

    QSqlQueryModel *modal = new QSqlQueryModel();

    conn.connOpen();
    QSqlQuery *qry = new QSqlQuery(conn.mydb);
    qry->prepare("select surname from kontakty");

    qry->exec();
    modal->setQuery(*qry);
    ui->comboBox ->setModel(modal);

    QDate data;
    data = QDate::fromString(ui->calendar->selectedDate().toString("dd-MM-yyyy"), "dd-MM-yyyy");
    ui->lineEdit_date->setText(data.toString());
}

Organizer::~Organizer()
{
    delete ui;
}

void Organizer::on_pb_go_contact_clicked()
{
    this -> hide();
    Contacts contacts;
    contacts.setModal(true);
    contacts.exec();
}

void Organizer::on_pb_add_meet_clicked()
{
    QString date;
//    date = QDate::fromString(ui->calendar->selectedDate().toString("dd-MM-yyyy");
    QDate data;
    data = QDate::fromString(ui->calendar->selectedDate().toString("dd-MM-yyyy"), "dd-MM-yyyy");
    ui->lineEdit_date->setText(data.toString());


    Login conn;
    QString  uczestnik, data2, notatki;
    uczestnik= ui -> comboBox ->currentText();
    data2= ui -> lineEdit_date->text();
    notatki= ui -> lineEdit_notes->text();

    if(!conn.connOpen()){
        qDebug()<<"Failed to open the database";
                return;
    }

    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("insert into spotkania ('Uczestnik Spotkania', 'Data Spotkania', Notatki) values ('"+uczestnik+"','"+data2+"','"+notatki+"')");
//     qry.prepare("insert into kontakty(name, surname, phone, mail, company) values ('"+name+"','"+surname+"','"+phone+"','"+mail+"','"+company+"')");
    if(qry.exec())  {
            QMessageBox::critical(this, tr("Edit"), tr("Updated"));
    }
    else{
        QMessageBox::critical(this, tr("error::"), qry.lastError().text());
    }


}

void Organizer::on_lineEdit_date_cursorPositionChanged(int arg1, int arg2)
{
    QDate data;
    data = QDate::fromString(ui->calendar->selectedDate().toString("dd-MM-yyyy"), "dd-MM-yyyy");
    ui->lineEdit_date->setText(data.toString());
}

void Organizer::on_calendar_clicked(const QDate &date)
{
    QDate data;
    data = QDate::fromString(ui->calendar->selectedDate().toString("dd-MM-yyyy"), "dd-MM-yyyy");
    ui->lineEdit_date->setText(data.toString());
}
