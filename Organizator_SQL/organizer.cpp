#include "organizer.h"
#include "ui_organizer.h"

Organizer::Organizer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Organizer)
{
    ui->setupUi(this);
}

Organizer::~Organizer()
{
    delete ui;
}
