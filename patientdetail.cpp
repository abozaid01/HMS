#include "patientdetail.h"
#include "ui_patientdetail.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include "patient.h"
#include <QMessageBox>
#include "adminportal.h"
#include "welcome.h"
#include <QDebug>

PatientDetail::PatientDetail(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PatientDetail)
{
    ui->setupUi(this);

    viewPatient();
}

PatientDetail::~PatientDetail()
{
    delete ui;

}


//----------------------- start view patient -----------------------
void PatientDetail::viewPatient()
{
    QSqlQueryModel *model = new QSqlQueryModel;

    admin.connOpen();
    QSqlQuery *qry = new QSqlQuery(admin.db);
    qry->prepare("SELECT * FROM Patient");
    qry->exec();

    model->setQuery(std::move(*qry));
    ui->tableView->setModel(model);
    admin.connClose();
    //qDebug() << (model->rowCount());
}
//------------------------- end view patient ------------------------------


//------------------------ start add patient ------------------------------
void PatientDetail::addPatient()
{

    //create new patient object
    Patient *p = new Patient(this);

    //grab the data from the GUI
    p->setId(ui->patient_id_1->text());
    p->setFirstName(ui->patient_first_name_1->text());
    //p->setLastName(ui->patient_last_name_1->text());
    //p->setAge(ui->patient_age_1->text());
    p->setPhone_number(ui->patient_phone_number_1->text());
    //p->setAddress(ui->patient_address_1->text());
    p->setGender(ui->patient_gender_1->currentText());
    p->setMarital_status(ui->patient_marital_status_1->currentText());
    p->setDOB(ui->patient_dateEdit_1->date());

    //CONSTRAINTS

    //Entity Integrity Constraints
    //No Primary key can be Null
    if(p->getId() == ""){
        QMessageBox *msgBox = new QMessageBox(this);
        msgBox->setIcon(QMessageBox::Warning);
        msgBox->setText("Patient SSN Can't Be NULL!");
        msgBox->setWindowTitle("Not Valid");
        msgBox->exec();
        return;
    }

    //Key Constraints
    //no two tuples can have the same values
    admin.connOpen();
    QSqlQuery *qry = new QSqlQuery(admin.db);
    qry->prepare("SELECT PSSN FROM Patient WHERE PSSN = '"+p->getId()+"'");
    qry->exec();
    admin.connClose();



    QMessageBox *msgBox = new QMessageBox(this);
    msgBox->setIcon(QMessageBox::Information);
    msgBox->setText("Patient Added Sucessfully.");
    msgBox->setWindowTitle("ADD");
    msgBox->exec();

    //connect the database and add new record
    /*admin.connOpen();
    QSqlQuery *qry = new QSqlQuery(admin.db);
    qry->prepare("INSERT INTO Patient (PSSN, Name, DOB, Sex, Status, Phone) VALUES('"+p->getId()+"', '"+p->getFirstName()+"', '"+p->getDOB().toString()+"', '"+p->getGender()+"', '"+p->getMarital_status()+"', '"+p->getPhone_number()+"')");
    qry->exec();
    admin.connClose();*/

    viewPatient();
}

//ADD BUTTON
void PatientDetail::on_add_pushButton_clicked()
{
    addPatient();


    //return the GUI to the default view
    ui->patient_id_1->setText("");
    ui->patient_first_name_1->setText("");
    //ui->patient_last_name_1->setText("");
    //ui->patient_age_1->setText("");
    ui->patient_phone_number_1->setText("");
    //ui->patient_address_1->setText("");
    ui->patient_gender_1->setCurrentIndex(-1);
    ui->patient_marital_status_1->setCurrentIndex(-1);
    ui->patient_dateEdit_1->setDate(QDate(2000,1,1));

}

//Home and Logout BUTTONS
void PatientDetail::on_home_pushButton_1_clicked()
{
    this->hide();
    AdminPortal *a = new AdminPortal(this);
    a->show();
}


void PatientDetail::on_logout_pushButton_1_clicked()
{
    this->hide();
    Welcome *w = new Welcome(this);
    w->show();
}


//----------------------------------- end add patient ------------------------------------------------------


//----------------------------------- start search patient ------------------------------------------------
QSqlQuery* PatientDetail::searchPatient(QString patient_id)
{
    admin.connOpen();
    QSqlQuery *qry = new QSqlQuery(admin.db);

    qry->prepare(" SELECT * FROM patient WHERE patient_id = '"+patient_id+"'");
    qry->exec();
    return qry;

}


//BUTTON
void PatientDetail::on_search_pushButton_2_clicked()  //Search patient
{
    QSqlQuery *qry = searchPatient(ui->patient_id_2->text());

    bool flag = true;

    while(qry->next()){

        ui->patient_first_name_2->setText(qry->value(1).toString());
        ui->patient_last_name_2->setText(qry->value(2).toString());
        ui->patient_age_2->setText(qry->value(3).toString());
        ui->patient_gender_2->setPlaceholderText(qry->value(4).toString());
        ui->patient_marital_status_2->setPlaceholderText(qry->value(5).toString());
        ui->patient_phone_number_2->setText(qry->value(6).toString());
        ui->patient_address_2->setText(qry->value(7).toString());

        QMessageBox *msgBox = new QMessageBox(this);
        msgBox->setIcon(QMessageBox::Information);
        msgBox->setText("Patient Found.");
        msgBox->setWindowTitle("Message");
        msgBox->exec();

        flag = false;
    }

    if(flag){
        QMessageBox *msgBox = new QMessageBox(this);
        msgBox->setIcon(QMessageBox::Information);
        msgBox->setText("Not Found!");
        msgBox->setWindowTitle("Message");
        msgBox->exec();

        //return the GUI to the default view
        ui->patient_id_2->setText("");
        ui->patient_first_name_2->setText("");
        ui->patient_last_name_2->setText("");
        ui->patient_age_2->setText("");
        ui->patient_phone_number_2->setText("");
        ui->patient_address_2->setText("");
        ui->patient_gender_2->setCurrentIndex(-1);
        ui->patient_marital_status_2->setCurrentIndex(-1);
    }


    admin.connClose();

}

//Home and Logout BUTTONS
void PatientDetail::on_home_pushButton_2_clicked()
{
    this->hide();
    AdminPortal *a = new AdminPortal(this);
    a->show();
}


void PatientDetail::on_logout_pushButton_2_clicked()
{
    this->hide();
    Welcome *w = new Welcome(this);
    w->show();
}


//--------------------------------- end search patient ------------------------------------------------------------


//------------------------- start delete patient ------------------------------------------------------------------

//Search BUTTON
void PatientDetail::on_search_pushButton_3_clicked()
{
    QSqlQuery *qry = searchPatient(ui->patient_id_3->text());

    bool flag = true;

    while(qry->next()){

        ui->patient_first_name_3->setText(qry->value(1).toString());
        ui->patient_last_name_3->setText(qry->value(2).toString());
        ui->patient_age_3->setText(qry->value(3).toString());
        ui->patient_gender_3->setPlaceholderText(qry->value(4).toString());
        ui->patient_marital_status_3->setPlaceholderText(qry->value(5).toString());
        ui->patient_phone_number_3->setText(qry->value(6).toString());
        ui->patient_address_3->setText(qry->value(7).toString());

        QMessageBox *msgBox = new QMessageBox(this);
        msgBox->setIcon(QMessageBox::Information);
        msgBox->setText("Patient Found.");
        msgBox->setWindowTitle("Message");
        msgBox->exec();

        ui->delete_pushButton->setEnabled(true);

        flag = false;
    }

    if(flag){
        QMessageBox *msgBox = new QMessageBox(this);
        msgBox->setIcon(QMessageBox::Information);
        msgBox->setText("Not Found!");
        msgBox->setWindowTitle("Message");
        msgBox->exec();
    }


    admin.connClose();

}

//delete BUTTON
void PatientDetail::on_delete_pushButton_clicked()
{
    int ret = QMessageBox::question(this, "Delete", "Patient will be deleted, Are you sure?",QMessageBox::Ok | QMessageBox::Cancel);
    if(ret == QMessageBox::Ok){
        QString patient_id = ui->patient_id_3->text();
        admin.connOpen();
        QSqlQuery *qry = new QSqlQuery(admin.db);

        qry->prepare("DELETE FROM patient WHERE Patient_ID = '"+patient_id+"'");
        qry->exec();
        admin.connClose();
    }

    viewPatient();

    //return the GUI to the default view
    ui->patient_id_3->setText("");
    ui->patient_first_name_3->setText("");
    ui->patient_last_name_3->setText("");
    ui->patient_age_3->setText("");
    ui->patient_phone_number_3->setText("");
    ui->patient_address_3->setText("");
    ui->patient_gender_3->setCurrentText("");                      /////////////////////////////////EDIT HERE !!!! /////////////////
    ui->patient_marital_status_3->setCurrentText("");             /////////////////////////////////EDIT HERE !!!! /////////////////

    ui->delete_pushButton->setEnabled(false);

}

//Home and Logout BUTTONS
void PatientDetail::on_home_pushButton_3_clicked()
{
    this->hide();
    AdminPortal *a = new AdminPortal(this);
    a->show();
}


void PatientDetail::on_logout_pushButton_3_clicked()
{
    this->hide();
    Welcome *w = new Welcome(this);
    w->show();
}


//----------------------------- end delete patinet ----------------------------------------------------------


//----------------------------------start update patient ----------------------------------------------------
//search BUTTON
void PatientDetail::on_search_pushButton_4_clicked()  //Search BUTTON and Update
{
    QSqlQuery *qry = searchPatient(ui->patient_id_4->text());

    bool flag = true;

    while(qry->next()){

        ui->patient_first_name_4->setText(qry->value(1).toString());
        ui->patient_last_name_4->setText(qry->value(2).toString());
        ui->patient_age_4->setText(qry->value(3).toString());
        ui->patient_gender_4->setPlaceholderText(qry->value(4).toString());
        ui->patient_marital_status_4->setPlaceholderText(qry->value(5).toString());
        ui->patient_phone_number_4->setText(qry->value(6).toString());
        ui->patient_address_4->setText(qry->value(7).toString());

        QMessageBox *msgBox = new QMessageBox(this);
        msgBox->setIcon(QMessageBox::Information);
        msgBox->setText("Patient Found.");
        msgBox->setWindowTitle("Message");
        msgBox->exec();

        ui->update_pushButton->setEnabled(true);

        flag = false;
    }

    if(flag){
        QMessageBox *msgBox = new QMessageBox(this);
        msgBox->setIcon(QMessageBox::Information);
        msgBox->setText("Not Found!");
        msgBox->setWindowTitle("Message");
        msgBox->exec();
    }


    admin.connClose();

}

//Update BUTTON
void PatientDetail::on_update_pushButton_clicked()
{
    int ret = QMessageBox::question(this, "Update", "Patient will be updated, Are you sure?",QMessageBox::Ok | QMessageBox::Cancel);
    if(ret == QMessageBox::Ok){
        QString patient_id = ui->patient_id_4->text();
        admin.connOpen();
        QSqlQuery *qry = new QSqlQuery(admin.db);

        //String = "UPDATE yourtable SET yourcolumn = '" + yourvealueintext + "' WHERE column = " + item_to_compare_the_position_of_Your_Column;
        qry->prepare("UPDATE patient SET First_Name = '"+ui->patient_first_name_4->text()+"' , Last_Name = '"+ui->patient_last_name_4->text()+"', Age = '"+ui->patient_age_4->text()+"', Gender = '"+ui->patient_gender_4->currentText()+"', Marital_Status = '"+ui->patient_marital_status_4->currentText()+"', Phone_Number = '"+ui->patient_phone_number_4->text()+"', Address = '"+ui->patient_address_4->text()+"' WHERE Patient_ID = '"+patient_id+"'");
        qry->exec();
        admin.connClose();

        QMessageBox *msgBox = new QMessageBox(this);
        msgBox->setIcon(QMessageBox::Information);
        msgBox->setText("Patient Updated Sucessfully.");
        msgBox->setWindowTitle("UPDATE");
        msgBox->exec();

        viewPatient();
    }

    ui->update_pushButton->setEnabled(false);
}

//Home and Logout BUTTONS
void PatientDetail::on_home_pushButton_4_clicked()
{
    this->hide();
    AdminPortal *a = new AdminPortal(this);
    a->show();
}


void PatientDetail::on_logout_pushButton_4_clicked()
{
    this->hide();
    Welcome *w = new Welcome(this);
    w->show();
}

//----------------------------------- end update patient -----------------------------------------------------------
