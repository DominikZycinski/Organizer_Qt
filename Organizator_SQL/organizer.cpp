#include "organizer.h"
#include "ui_organizer.h"
#include "login.h"

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
    ui->edit_date->setText(data.toString());
}
