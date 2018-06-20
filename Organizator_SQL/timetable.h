#ifndef TIMETABLE_H
#define TIMETABLE_H

#include <QDialog>
#include "login.h"
#include "contacts.h"
#include "organizer.h"
namespace Ui {
class Timetable;
}

class Timetable : public QDialog
{
    Q_OBJECT

public:
    explicit Timetable(QWidget *parent = 0);
    ~Timetable();
    void loadTimetable();

private slots:

    void on_pb_add_meet2_clicked();

    void on_pb_update_meet_clicked();

    void on_tableView_timetable_activated(const QModelIndex &index);

    void on_pb_delete_meet_clicked();

private:
    Ui::Timetable *ui;
};

#endif // TIMETABLE_H
