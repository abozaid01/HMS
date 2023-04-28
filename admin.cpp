#include "admin.h"
#include "ui_admin.h"
#include <QDebug>
#include <QSqlQuery>
#include "adminportal.h"

Admin::Admin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Admin)
{
    ui->setupUi(this);
    connOpen();
}

Admin::~Admin()
{
    delete ui;
}

bool Admin::connOpen()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Users/Asaid/Desktop/HMS/myDb.db");
    if(!db.open()){
        qDebug()<<("Failed to open the database!");
        return false;
    }else{
        qDebug()<<("Connected database........");
        return true;
    }
}

void Admin::connClose()
{
    db.close();
    db.removeDatabase(QSqlDatabase::defaultConnection);

}

void Admin::on_adminLoginPushButton_clicked()
{

    int count = 0;
    //.........................................................Exception.....................................//
    try {
        adminUsername = ui ->adminUsername->text();   // login and get the text of username and password form user input.
        adminPassword = ui->adminPassword->text();

        connOpen();
        QSqlQuery qry;
        qry.prepare("SELECT * FROM Admin where ASSN='"+adminUsername + "'and Security_ID = '"+adminPassword+"'");

        if(qry.exec()){
            while(qry.next())
                count++;
            qDebug() << count;
            if(count==1){
                connClose();    // close the database before open next window
                qDebug() << "login successfully!";
                 this->hide();
                AdminPortal *adminP = new AdminPortal(this);
                adminP->show();

            }
            else
                throw("Error");

        }
    }
    catch (...) {
        ui->label ->setText("Username or password is NOT correct.");
        qDebug() << "Catch Error： Username or password or work code is NOT correct. ";
    }


}

