#ifndef PATIENTDETAIL_H
#define PATIENTDETAIL_H

#include <QDialog>
#include "admin.h"


namespace Ui {
class PatientDetail;
}

class PatientDetail : public QDialog
{
    Q_OBJECT

public:
    explicit PatientDetail(QWidget *parent = nullptr);
    ~PatientDetail();
    QSqlDatabase db;
    void viewPatient();
    void addPatient();
    QSqlQuery* searchPatient(QString);


private slots:


    void on_add_pushButton_clicked();

    void on_search_pushButton_2_clicked();

    void on_search_pushButton_3_clicked();

    void on_search_pushButton_4_clicked();

    void on_delete_pushButton_clicked();

    void on_update_pushButton_clicked();

    void on_home_pushButton_1_clicked();

    void on_logout_pushButton_1_clicked();

    void on_home_pushButton_2_clicked();

    void on_logout_pushButton_2_clicked();

    void on_home_pushButton_3_clicked();

    void on_logout_pushButton_3_clicked();

    void on_home_pushButton_4_clicked();

    void on_logout_pushButton_4_clicked();

private:
    Ui::PatientDetail *ui;
    Admin admin;
};

#endif // PATIENTDETAIL_H
