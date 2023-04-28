#ifndef RECEPTIONISTDETAIL_H
#define RECEPTIONISTDETAIL_H

#include <QDialog>
#include "admin.h"

namespace Ui {
class ReceptionistDetail;
}

class ReceptionistDetail : public QDialog
{
    Q_OBJECT

public:
    explicit ReceptionistDetail(QWidget *parent = nullptr);
    ~ReceptionistDetail();
    QSqlDatabase db;
    void viewReceptionist();
    void addReceptionist();
    QSqlQuery* searchReceptionist(QString);

private slots:
    void on_home_pushButton_1_clicked();

    void on_logout_pushButton_1_clicked();

    void on_home_pushButton_2_clicked();

    void on_logout_pushButton_2_clicked();

    void on_home_pushButton_3_clicked();

    void on_logout_pushButton_3_clicked();

    void on_home_pushButton_4_clicked();

    void on_logout_pushButton_4_clicked();

    void on_add_pushButton_clicked();

    void on_search_pushButton_2_clicked();

    void on_search_pushButton_3_clicked();

    void on_delete_pushButton_clicked();

    void on_search_pushButton_4_clicked();

    void on_update_pushButton_clicked();

private:
    Ui::ReceptionistDetail *ui;
    Admin admin;
};

#endif // RECEPTIONISTDETAIL_H
