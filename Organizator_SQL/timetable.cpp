#include "timetable.h"
#include "ui_timetable.h"

Timetable::Timetable(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Timetable)
{
    ui->setupUi(this);
}

Timetable::~Timetable()
{
    delete ui;
}
