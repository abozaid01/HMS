#include "welcome.h"
#include "ui_welcome.h"
#include "admin.h"

Welcome::Welcome(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Welcome)
{
    ui->setupUi(this);
}

Welcome::~Welcome()
{
    delete ui;
}



void Welcome::on_adminPushButton_clicked()
{
    this->hide();
    Admin *admin = new Admin(this);
    admin->show();
}


void Welcome::on_receptionstPushButton_clicked()
{

}


void Welcome::on_doctorPushButton_clicked()
{

}



