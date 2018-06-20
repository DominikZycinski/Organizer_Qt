#ifndef TIMETABLE_H
#define TIMETABLE_H

#include <QDialog>

namespace Ui {
class Timetable;
}

class Timetable : public QDialog
{
    Q_OBJECT

public:
    explicit Timetable(QWidget *parent = 0);
    ~Timetable();

private:
    Ui::Timetable *ui;
};

#endif // TIMETABLE_H
