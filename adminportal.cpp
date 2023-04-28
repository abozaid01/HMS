#include "adminportal.h"
#include "ui_adminportal.h"
#include "patientdetail.h"
#include "receptionistdetail.h"
#include "doctordetail.h"
#include "welcome.h"

AdminPortal::AdminPortal(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminPortal)
{
    ui->setupUi(this);
}

AdminPortal::~AdminPortal()
{
    delete ui;
}


void AdminPortal::on_patientButton_clicked()
{
    PatientDetail *patientDetails = new PatientDetail(this);
    this->hide();
    patientDetails->show();
}




void AdminPortal::on_receptionistButton_clicked()
{
    ReceptionistDetail *receptionistDetails = new ReceptionistDetail(this);
    this->hide();
    receptionistDetails->show();
}

void AdminPortal::on_doctorButton_clicked()
{
    DoctorDetail *doctorDetails = new DoctorDetail(this);
    this->hide();
    doctorDetails->show();
}

void AdminPortal::on_logout_pushButton_1_clicked()
{
    this->hide();
    Welcome *w = new Welcome(this);
    w->show();
}




