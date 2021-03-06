#ifndef CONTACTS_H
#define CONTACTS_H

#include <QDialog>

namespace Ui {
class Contacts;
}

class Contacts : public QDialog
{
    Q_OBJECT

public:
    explicit Contacts(QWidget *parent = 0);
    ~Contacts();

private slots:
    void on_pb_add_contact_clicked();

    void on_pb_update_contact_clicked();

    void on_pb_delete_contact_clicked();

    void on_pb_sort_name_clicked();

    void on_pb_sort_surname_clicked();

    void on_pb_sort_company_clicked();
    void load_contacts();
    void on_tableView_activated(const QModelIndex &index);

private:
    Ui::Contacts *ui;
};

#endif // CONTACTS_H
