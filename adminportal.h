#ifndef ADMINPORTAL_H
#define ADMINPORTAL_H

#include <QDialog>

namespace Ui {
class AdminPortal;
}

class AdminPortal : public QDialog
{
    Q_OBJECT

public:
    explicit AdminPortal(QWidget *parent = nullptr);
    ~AdminPortal();

private slots:
    void on_patientButton_clicked();


    void on_receptionistButton_clicked();

    void on_logout_pushButton_1_clicked();

    void on_doctorButton_clicked();

private:
    Ui::AdminPortal *ui;
};

#endif // ADMINPORTAL_H
