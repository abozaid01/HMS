#include "doctordetail.h"
#include "ui_doctordetail.h"
#include "adminportal.h"
#include "welcome.h"
#include "doctor.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>

DoctorDetail::DoctorDetail(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DoctorDetail)
{
    ui->setupUi(this);

    viewDoctor();
}

DoctorDetail::~DoctorDetail()
{
    delete ui;
}


//----------------------- start view Doctor -----------------------
void DoctorDetail::viewDoctor()
{
    QSqlQueryModel *model = new QSqlQueryModel;

        admin.connOpen();
        QSqlQuery *qry = new QSqlQuery(admin.db);
        qry->prepare("select * from Employee as E, Doctor as D where E.ESSN = D.DSSN");

        qry->exec();

        model->setQuery(std::move(*qry));
        ui->tableView->setModel(model);
        admin.connClose();;

}
//------------------------- end view Doctor ------------------------------

//------------------------ start add doctor ------------------------------

bool DoctorDetail::addDoctor()
{
    //create new Doctor object
    Doctor *d = new Doctor(this);

    //grab the data from the GUI
    d->setSSN(ui->doctor_ssn_1->text());
    d->setName(ui->doctor_name_1->text());
    d->setDOB(ui->doctor_DOB_1->text());
    d->setPhone_number(ui->doctor_phone_number_1->text());
    d->setSex(ui->doctor_sex_1->currentText());
    d->setWork_Hours(ui->doctor_workHours_1->text());
    d->setSalary(ui->doctor_salary_1->text());
    d->setDepartment(ui->doctor_department_1->currentText());
    d->setSpecialization(ui->doctor_specialization_1->text());

    //---------CONSTRAINTS ------------

    //Entity Integrity Constraints
    //No Primary key can be Null
    if(d->getSSN() == ""){
        QMessageBox *msgBox = new QMessageBox(this);
        msgBox->setIcon(QMessageBox::Warning);
        msgBox->setText("Primary key DSSN Can't Be NULL!");
        msgBox->setWindowTitle("Not Valid");
        msgBox->exec();
        return false;
    }

    //Key Constraints
    //no two tuples can have the same values
    bool flag1,flag2 = false;
    admin.connOpen();
    QSqlQuery *qry4 = new QSqlQuery(admin.db);
    qry4->prepare("SELECT DSSN FROM Doctor WHERE DSSN = '"+d->getSSN()+"'");
    qry4->exec();
    flag1 = qry4->first();
    admin.connClose();

    admin.connOpen();
    QSqlQuery *qry5 = new QSqlQuery(admin.db);
    qry5->prepare("SELECT ESSN FROM EMPLOYEE WHERE ESSN = '"+d->getSSN()+"'");
    qry5->exec();
    flag2 = qry5->first();
    admin.connClose();

    if(flag1||flag2){
        QMessageBox *msgBox = new QMessageBox(this);
        msgBox->setIcon(QMessageBox::Warning);
        msgBox->setText("no two Primary key DSSN Can have the same value!");
        msgBox->setWindowTitle("Not Valid");
        msgBox->exec();
        return false;
    }

    //Referntial Integrity Constraints
    //Foriegn key MUST be exist (same value or null)
    //no Referntial Integrity Constraints

    //------------End Constraints-------------------

    //connect the database and add new record
    admin.connOpen();
    QSqlQuery *qry1 = new QSqlQuery(admin.db);
    qry1->prepare("INSERT INTO EMPLOYEE (ESSN, Name, Salary, Work_Hours, DOB, Sex, Phone) VALUES('"+d->getSSN()+"','"+d->getName()+"','"+d->getSalary()+"','"+d->getWork_Hours()+"','"+d->getDOB()+"','"+d->getSex()+"','"+d->getPhone_number()+"')");
    qry1->exec();
    admin.connClose();

    admin.connOpen();
    QSqlQuery *qry2 = new QSqlQuery(admin.db);
    qry2->prepare("INSERT INTO Doctor (DSSN, D_D_Name, Specialization) VALUES(  '"+d->getSSN()+"','"+d->getDepartment()+"','"+d->getSpecialization()+"'  )");
    qry2->exec();
    admin.connClose();

    admin.connOpen();
    QSqlQuery *qry3 = new QSqlQuery(admin.db);
    qry3->prepare("UPDATE EMPLOYEE SET E_ASSN = 1001 WHERE ESSN = '"+d->getSSN()+"'");
    qry3->exec();

    viewDoctor();

    return true;
}

//ADD Button
void DoctorDetail::on_add_pushButton_clicked()
{
    if(addDoctor()){

        QMessageBox *msgBox = new QMessageBox(this);
        msgBox->setIcon(QMessageBox::Information);
        msgBox->setText("doctor Added Sucessfully.");
        msgBox->setWindowTitle("ADD");
        msgBox->exec();
    }

    //return the GUI to the default
    ui->doctor_ssn_1->setText("");
    ui->doctor_name_1->setText("");
    ui->doctor_DOB_1->setDate(QDate(2000,1,1));
    ui->doctor_phone_number_1->setText("");
    ui->doctor_sex_1->setCurrentIndex(-1);
    ui->doctor_workHours_1->setText("");
    ui->doctor_salary_1->setText("");
    ui->doctor_department_1->setCurrentIndex(-1);
    ui->doctor_specialization_1->setText("");
}

//Home and Logout BUTTONS
void DoctorDetail::on_home_pushButton_1_clicked()
{
    this->hide();
    AdminPortal *a = new AdminPortal(this);
    a->show();
}


void DoctorDetail::on_logout_pushButton_1_clicked()
{
    this->hide();
    Welcome *w = new Welcome(this);
    w->show();
}

//----------------------------------- end add doctor ------------------------------------------------------


//----------------------------------- start search doctor ------------------------------------------------

QSqlQuery* DoctorDetail::searchDoctor(QString DSSN)
{
    admin.connOpen();
    QSqlQuery *qry = new QSqlQuery(admin.db);

    qry->prepare(" select * from Employee as E, Doctor as D where E.ESSN = '"+DSSN+"'");
    qry->exec();
    return qry;

}

//SEARCH Button
void DoctorDetail::on_search_pushButton_2_clicked()
{
    QSqlQuery *qry = searchDoctor(ui->doctor_ssn_2->text());

    bool flag = true;

    if(qry->next()){

//        qDebug() << qry->value(4); //QString
//        qDebug() << qry->value(4).toDate(); //Invalid
//        qDebug() << qry->value(4).toDateTime(); //Invalid

        //ui->doctor_DOB_2->setDate(QDate(2000,1,1));

        ui->doctor_name_2->setText(qry->value(1).toString());
        ui->doctor_salary_2->setText(qry->value(2).toString());
        ui->doctor_workHours_2->setText(qry->value(3).toString());
        ui->doctor_DOB_2->setDate(QDate(qry->value(4).toDate()));                       /////EDIT HERE///////
        ui->doctor_sex_2->setPlaceholderText(qry->value(5).toString());
        ui->doctor_phone_number_2->setText(qry->value(6).toString());
        ui->doctor_department_2->setPlaceholderText(qry->value(9).toString());
        ui->doctor_specialization_2->setText(qry->value(10).toString());


        QMessageBox *msgBox = new QMessageBox(this);
        msgBox->setIcon(QMessageBox::Information);
        msgBox->setText("Doctor Found.");
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
        ui->doctor_ssn_2->setText("");
        ui->doctor_name_2->setText("");
        ui->doctor_DOB_2->setDate(QDate(2000,1,1));
        ui->doctor_phone_number_2->setText("");
        ui->doctor_sex_2->setCurrentIndex(-1);
        ui->doctor_workHours_2->setText("");
        ui->doctor_salary_2->setText("");
        ui->doctor_department_2->setCurrentIndex(-1);
        ui->doctor_specialization_2->setText("");
    }


    admin.connClose();
}

//Home and Logout BUTTONS
void DoctorDetail::on_home_pushButton_2_clicked()
{
    this->hide();
    AdminPortal *a = new AdminPortal(this);
    a->show();
}


void DoctorDetail::on_logout_pushButton_2_clicked()
{
    this->hide();
    Welcome *w = new Welcome(this);
    w->show();
}

//----------------------------------- end search doctor ------------------------------------------------------

//----------------------------------- start delete doctor ------------------------------------------------


//SEARCH Button
void DoctorDetail::on_search_pushButton_3_clicked()
{
    QSqlQuery *qry = searchDoctor(ui->doctor_ssn_3->text());

        bool flag = true;

        if(qry->next()){

            //ui->doctor_DOB_2->setDate(QDate(2000,1,1));

            ui->doctor_name_3->setText(qry->value(1).toString());
            ui->doctor_salary_3->setText(qry->value(2).toString());
            ui->doctor_workHours_3->setText(qry->value(3).toString());
            ui->doctor_DOB_3->setDate(QDate(qry->value(4).toDate()));                       /////EDIT HERE///////
            ui->doctor_sex_3->setPlaceholderText(qry->value(5).toString());
            ui->doctor_phone_number_3->setText(qry->value(6).toString());
            ui->doctor_department_3->setPlaceholderText(qry->value(9).toString());
            ui->doctor_specialization_3->setText(qry->value(10).toString());

            QMessageBox *msgBox = new QMessageBox(this);
            msgBox->setIcon(QMessageBox::Information);
            msgBox->setText("Doctor Found.");
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

//Delete Button
void DoctorDetail::on_delete_pushButton_clicked()
{
    int ret = QMessageBox::question(this, "Delete", "Doctor will be deleted from EMPLOYEE Database, Are you sure?",QMessageBox::Ok | QMessageBox::Cancel);
    if(ret == QMessageBox::Ok){
        QString DSSN = ui->doctor_ssn_3->text();
        admin.connOpen();
        QSqlQuery *qry = new QSqlQuery(admin.db);

        qry->prepare("DELETE FROM Doctor WHERE DSSN = '"+DSSN+"'");
        qry->exec();
        admin.connClose();

        admin.connOpen();
        QSqlQuery *qry2 = new QSqlQuery(admin.db);

        qry2->prepare("DELETE FROM EMPLOYEE WHERE ESSN = '"+DSSN+"'");
        qry2->exec();
        admin.connClose();
    }

    viewDoctor();

    //return the GUI to the default view
    ui->doctor_ssn_3->setText("");
    ui->doctor_name_3->setText("");
    ui->doctor_DOB_3->setDate(QDate(2000,1,1));
    ui->doctor_phone_number_3->setText("");
    ui->doctor_sex_3->setCurrentIndex(-1);
    ui->doctor_workHours_3->setText("");
    ui->doctor_salary_3->setText("");
    ui->doctor_department_3->setCurrentIndex(-1);
    ui->doctor_specialization_3->setText("");

    ui->delete_pushButton->setEnabled(false);
}

//Home and Logout BUTTONS
void DoctorDetail::on_home_pushButton_3_clicked()
{
    this->hide();
    AdminPortal *a = new AdminPortal(this);
    a->show();
}


void DoctorDetail::on_logout_pushButton_3_clicked()
{
    this->hide();
    Welcome *w = new Welcome(this);
    w->show();
}
//----------------------------------- end delete doctor ------------------------------------------------------

//----------------------------------- start update doctor ------------------------------------------------

//Search Button
void DoctorDetail::on_search_pushButton_4_clicked()
{
    QSqlQuery *qry = searchDoctor(ui->doctor_ssn_4->text());

    bool flag = true;

    if(qry->next()){

        //ui->doctor_DOB_2->setDate(QDate(2000,1,1));

        ui->doctor_name_4->setText(qry->value(1).toString());
        ui->doctor_salary_4->setText(qry->value(2).toString());
        ui->doctor_workHours_4->setText(qry->value(3).toString());
        ui->doctor_DOB_4->setDate(QDate(qry->value(4).toDate()));                       /////EDIT HERE///////
        ui->doctor_sex_4->setPlaceholderText(qry->value(5).toString());
        ui->doctor_phone_number_4->setText(qry->value(6).toString());
        ui->doctor_department_4->setPlaceholderText(qry->value(9).toString());
        ui->doctor_specialization_4->setText(qry->value(10).toString());

        QMessageBox *msgBox = new QMessageBox(this);
        msgBox->setIcon(QMessageBox::Information);
        msgBox->setText("Doctor Found.");
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

//update Button
void DoctorDetail::on_update_pushButton_clicked()
{
    int ret = QMessageBox::question(this, "Update", "Doctor will be updated in EMPLOYEE Table, Are you sure?",QMessageBox::Ok | QMessageBox::Cancel);
    if(ret == QMessageBox::Ok){
        QString DSSN = ui->doctor_ssn_4->text();

        //String = "UPDATE yourtable SET yourcolumn = '" + yourvealueintext + "' WHERE column = " + item_to_compare_the_position_of_Your_Column;
        admin.connOpen();
        QSqlQuery *qry2 = new QSqlQuery(admin.db);
        qry2->prepare("UPDATE EMPLOYEE SET Name = '"+ui->doctor_name_4->text()+"' , Salary = '"+ui->doctor_salary_4->text()+"', Work_Hours = '"+ui->doctor_workHours_4->text()+"', DOB = '"+ui->doctor_DOB_4->text()+"', Sex = '"+ui->doctor_sex_4->currentText()+"', Phone = '"+ui->doctor_phone_number_4->text()+"'  WHERE ESSN = '"+DSSN+"'");
        qry2->exec();
        admin.connClose();

        admin.connOpen();
        QSqlQuery *qry = new QSqlQuery(admin.db);
        qry->prepare("UPDATE doctor SET D_D_Name = '"+ui->doctor_department_4->currentText()+"' , Specialization = '"+ui->doctor_specialization_4->text()+"' WHERE DSSN = '"+DSSN+"'");
        qry->exec();
        admin.connClose();

        QMessageBox *msgBox = new QMessageBox(this);
        msgBox->setIcon(QMessageBox::Information);
        msgBox->setText("Doctor Updated Sucessfully.");
        msgBox->setWindowTitle("UPDATE");
        msgBox->exec();

        viewDoctor();
    }

    ui->update_pushButton->setEnabled(false);
}

//Home and Logout BUTTONS
void DoctorDetail::on_home_pushButton_4_clicked()
{
    this->hide();
    AdminPortal *a = new AdminPortal(this);
    a->show();
}


void DoctorDetail::on_logout_pushButton_4_clicked()
{
    this->hide();
    Welcome *w = new Welcome(this);
    w->show();
}
//----------------------------------- end update doctor ------------------------------------------------------






