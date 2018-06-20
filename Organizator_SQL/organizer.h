#ifndef ORGANIZER_H
#define ORGANIZER_H

#include <QDialog>
#include "contacts.h"
#include "timetable.h"
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

    void on_lineEdit_date_cursorPositionChanged(int arg1, int arg2);

    void on_calendar_clicked(const QDate &date);

    void on_pb_go_timetable_clicked();



private:
    Ui::Organizer *ui;
};

#endif // ORGANIZER_H
