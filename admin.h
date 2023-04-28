#ifndef ADMIN_H
#define ADMIN_H

#include <QDialog>
#include <QtSql/QSqlDatabase>

namespace Ui {
class Admin;
}

class Admin : public QDialog
{
    Q_OBJECT

public:
    explicit Admin(QWidget *parent = nullptr);
    ~Admin();

    QSqlDatabase db;
    bool connOpen();
    void connClose();


private slots:
    void on_adminLoginPushButton_clicked();

private:
    Ui::Admin *ui;
    QString adminUsername;
    QString adminPassword;
};

#endif // ADMIN_H
