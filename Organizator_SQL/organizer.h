#ifndef ORGANIZER_H
#define ORGANIZER_H

#include <QDialog>

namespace Ui {
class Organizer;
}

class Organizer : public QDialog
{
    Q_OBJECT

public:
    explicit Organizer(QWidget *parent = 0);
    ~Organizer();

private:
    Ui::Organizer *ui;
};

#endif // ORGANIZER_H
