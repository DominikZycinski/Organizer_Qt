#ifndef ORGANIZER_H
#define ORGANIZER_H

#include <QDialog>
#include "contacts.h"

namespace Ui {
class Organizer;
}

class Organizer : public QDialog
{
    Q_OBJECT

public:

    explicit Organizer(QWidget *parent = 0);
    ~Organizer();

private slots:
    void on_pb_go_contact_clicked();

    void on_pb_add_meet_clicked();

private:
    Ui::Organizer *ui;
};

#endif // ORGANIZER_H
