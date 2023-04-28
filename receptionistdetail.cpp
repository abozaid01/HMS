#include "receptionistdetail.h"
#include "ui_receptionistdetail.h"
#include "receptionist.h"
#include "adminportal.h"
#include "welcome.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>

ReceptionistDetail::ReceptionistDetail(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReceptionistDetail)
{
    ui->setupUi(this);

    viewReceptionist();
}

ReceptionistDetail::~ReceptionistDetail()
{
    delete ui;
}


//----------------------- start view Receptionist -----------------------
void ReceptionistDetail::viewReceptionist()
{
    QSqlQueryModel *model = new QSqlQueryModel;

    admin.connOpen();
    QSqlQuery *qry = new QSqlQuery(admin.db);
    qry->prepare("SELECT * FROM Receptionist");
    qry->exec();

    model->setQuery(std::move(*qry));
    ui->tableView->setModel(model);
    admin.connClose();
    //qDebug() << (model->rowCount());
}
//------------------------- end view receptionist ------------------------------


//------------------------ start add receptionist ------------------------------

void ReceptionistDetail::addReceptionist()
{
    //create new receptionist object
    Receptionist *r = new Receptionist(this);

    //grab the data from the GUI
    r->setId(ui->receptionist_id_1->text());
    r->setFirstName(ui->receptionist_first_name_1->text());
    r->setLastName(ui->receptionist_last_name_1->text());
    r->setAge(ui->receptionist_age_1->text());
    r->setPhone_number(ui->receptionist_phone_number_1->text());
    r->setAddress(ui->receptionist_address_1->text());
    r->setGender(ui->receptionist_gender_1->currentText());
    r->setMarital_status(ui->receptionist_marital_status_1->currentText());

    //connect the database and add new record
    admin.connOpen();
    QSqlQuery *qry = new QSqlQuery(admin.db);
    qry->prepare("INSERT INTO Receptionist (Receptionist_ID, First_Name, Last_Name, Age, Gender, Marital_Status, Phone_Number, Address) VALUES('"+r->getId()+"', '"+r->getFirstName()+"', '"+r->getLastName()+"', '"+r->getAge()+"', '"+r->getGender()+"', '"+r->getMarital_status()+"', '"+r->getPhone_number()+"','"+r->getAddress()+"')");
    qry->exec();
    admin.connClose();

    viewReceptionist();
}

//ADD BUTTON
void ReceptionistDetail::on_add_pushButton_clicked()
{
    addReceptionist();

    QMessageBox *msgBox = new QMessageBox(this);
    msgBox->setIcon(QMessageBox::Information);
    msgBox->setText("receptionist Added Sucessfully.");
    msgBox->setWindowTitle("ADD");
    msgBox->exec();

    //return the GUI to the default view
    ui->receptionist_id_1->setText("");
    ui->receptionist_first_name_1->setText("");
    ui->receptionist_last_name_1->setText("");
    ui->receptionist_age_1->setText("");
    ui->receptionist_phone_number_1->setText("");
    ui->receptionist_address_1->setText("");
    ui->receptionist_gender_1->setCurrentIndex(-1);
    ui->receptionist_marital_status_1->setCurrentIndex(-1);

}

//Home and Logout BUTTONS
void ReceptionistDetail::on_home_pushButton_1_clicked()
{
    this->hide();
    AdminPortal *a = new AdminPortal(this);
    a->show();
}


void ReceptionistDetail::on_logout_pushButton_1_clicked()
{
    this->hide();
    Welcome *w = new Welcome(this);
    w->show();
}

//----------------------------------- end add receptionist ------------------------------------------------------


//----------------------------------- start search receptionist ------------------------------------------------

QSqlQuery* ReceptionistDetail::searchReceptionist(QString receptionist_id)
{
    admin.connOpen();
    QSqlQuery *qry = new QSqlQuery(admin.db);

    qry->prepare(" SELECT * FROM receptionist WHERE receptionist_id = '"+receptionist_id+"'");
    qry->exec();
    return qry;

}

//BUTTON
void ReceptionistDetail::on_search_pushButton_2_clicked()
{
    QSqlQuery *qry = searchReceptionist(ui->receptionist_id_2->text());

    bool flag = true;

    while(qry->next()){

        ui->receptionist_first_name_2->setText(qry->value(1).toString());
        ui->receptionist_last_name_2->setText(qry->value(2).toString());
        ui->receptionist_age_2->setText(qry->value(3).toString());
        ui->receptionist_gender_2->setPlaceholderText(qry->value(4).toString());
        ui->receptionist_marital_status_2->setPlaceholderText(qry->value(5).toString());
        ui->receptionist_phone_number_2->setText(qry->value(6).toString());
        ui->receptionist_address_2->setText(qry->value(7).toString());

        QMessageBox *msgBox = new QMessageBox(this);
        msgBox->setIcon(QMessageBox::Information);
        msgBox->setText("Receptionist Found.");
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
        ui->receptionist_id_2->setText("");
        ui->receptionist_first_name_2->setText("");
        ui->receptionist_last_name_2->setText("");
        ui->receptionist_age_2->setText("");
        ui->receptionist_phone_number_2->setText("");
        ui->receptionist_address_2->setText("");
        ui->receptionist_gender_2->setCurrentIndex(-1);
        ui->receptionist_marital_status_2->setCurrentIndex(-1);
    }


    admin.connClose();
}

//Home and Logout BUTTONS
void ReceptionistDetail::on_home_pushButton_2_clicked()
{
    this->hide();
    AdminPortal *a = new AdminPortal(this);
    a->show();
}


void ReceptionistDetail::on_logout_pushButton_2_clicked()
{
    this->hide();
    Welcome *w = new Welcome(this);
    w->show();
}

//----------------------------------- end search receptionist ------------------------------------------------------

//----------------------------------- start delete receptionist ------------------------------------------------

//Search BUTTON
void ReceptionistDetail::on_search_pushButton_3_clicked()
{
    QSqlQuery *qry = searchReceptionist(ui->receptionist_id_3->text());

    bool flag = true;

    while(qry->next()){

        ui->receptionist_first_name_3->setText(qry->value(1).toString());
        ui->receptionist_last_name_3->setText(qry->value(2).toString());
        ui->receptionist_age_3->setText(qry->value(3).toString());
        ui->receptionist_gender_3->setPlaceholderText(qry->value(4).toString());
        ui->receptionist_marital_status_3->setPlaceholderText(qry->value(5).toString());
        ui->receptionist_phone_number_3->setText(qry->value(6).toString());
        ui->receptionist_address_3->setText(qry->value(7).toString());

        QMessageBox *msgBox = new QMessageBox(this);
        msgBox->setIcon(QMessageBox::Information);
        msgBox->setText("Receptionist Found.");
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

        //return the GUI to the default view
        ui->receptionist_id_3->setText("");
        ui->receptionist_first_name_3->setText("");
        ui->receptionist_last_name_3->setText("");
        ui->receptionist_age_3->setText("");
        ui->receptionist_phone_number_3->setText("");
        ui->receptionist_address_3->setText("");
        ui->receptionist_gender_3->setCurrentIndex(-1);               /////////////////////////////////EDIT HERE !!!! /////////////////
        ui->receptionist_marital_status_3->setCurrentIndex(-1);      /////////////////////////////////EDIT HERE !!!! /////////////////
    }


    admin.connClose();
}

//delete BUTTON
void ReceptionistDetail::on_delete_pushButton_clicked()
{
    int ret = QMessageBox::question(this, "Delete", "Receptionist will be deleted, Are you sure?",QMessageBox::Ok | QMessageBox::Cancel);
    if(ret == QMessageBox::Ok){
        QString receptionist_id = ui->receptionist_id_3->text();
        admin.connOpen();
        QSqlQuery *qry = new QSqlQuery(admin.db);

        qry->prepare("DELETE FROM receptionist WHERE Receptionist_ID = '"+receptionist_id+"'");
        qry->exec();
        admin.connClose();
    }

    viewReceptionist();

    //return the GUI to the default view
    ui->receptionist_id_3->setText("");
    ui->receptionist_first_name_3->setText("");
    ui->receptionist_last_name_3->setText("");
    ui->receptionist_age_3->setText("");
    ui->receptionist_phone_number_3->setText("");
    ui->receptionist_address_3->setText("");
    ui->receptionist_gender_3->setCurrentIndex(-1);
    ui->receptionist_marital_status_3->setCurrentIndex(-1);

    ui->delete_pushButton->setEnabled(false);
}

//Home and Logout BUTTONS
void ReceptionistDetail::on_home_pushButton_3_clicked()
{
    this->hide();
    AdminPortal *a = new AdminPortal(this);
    a->show();
}


void ReceptionistDetail::on_logout_pushButton_3_clicked()
{
    this->hide();
    Welcome *w = new Welcome(this);
    w->show();
}
//----------------------------------- end delete receptionist ------------------------------------------------------

//----------------------------------- start update receptionist ------------------------------------------------


//Search BUTTON
void ReceptionistDetail::on_search_pushButton_4_clicked()
{
    QSqlQuery *qry = searchReceptionist(ui->receptionist_id_4->text());

    bool flag = true;

    while(qry->next()){

        ui->receptionist_first_name_4->setText(qry->value(1).toString());
        ui->receptionist_last_name_4->setText(qry->value(2).toString());
        ui->receptionist_age_4->setText(qry->value(3).toString());
        ui->receptionist_gender_4->setPlaceholderText(qry->value(4).toString());
        ui->receptionist_marital_status_4->setPlaceholderText(qry->value(5).toString());
        ui->receptionist_phone_number_4->setText(qry->value(6).toString());
        ui->receptionist_address_4->setText(qry->value(7).toString());

        QMessageBox *msgBox = new QMessageBox(this);
        msgBox->setIcon(QMessageBox::Information);
        msgBox->setText("Receptionist Found.");
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

        //return the GUI to the default view
        ui->receptionist_id_4->setText("");
        ui->receptionist_first_name_4->setText("");
        ui->receptionist_last_name_4->setText("");
        ui->receptionist_age_4->setText("");
        ui->receptionist_phone_number_4->setText("");
        ui->receptionist_address_4->setText("");
        ui->receptionist_gender_4->setCurrentIndex(-1);
        ui->receptionist_marital_status_4->setCurrentIndex(-1);
    }


    admin.connClose();
}

//Updat BUTTON
void ReceptionistDetail::on_update_pushButton_clicked()
{
    int ret = QMessageBox::question(this, "Update", "Receptionist will be updated, Are you sure?",QMessageBox::Ok | QMessageBox::Cancel);
    if(ret == QMessageBox::Ok){
        QString receptionist_id = ui->receptionist_id_4->text();
        admin.connOpen();
        QSqlQuery *qry = new QSqlQuery(admin.db);

        //String = "UPDATE yourtable SET yourcolumn = '" + yourvealueintext + "' WHERE column = " + item_to_compare_the_position_of_Your_Column;
        qry->prepare("UPDATE receptionist SET First_Name = '"+ui->receptionist_first_name_4->text()+"' , Last_Name = '"+ui->receptionist_last_name_4->text()+"', Age = '"+ui->receptionist_age_4->text()+"', Gender = '"+ui->receptionist_gender_4->currentText()+"', Marital_Status = '"+ui->receptionist_marital_status_4->currentText()+"', Phone_Number = '"+ui->receptionist_phone_number_4->text()+"', Address = '"+ui->receptionist_address_4->text()+"' WHERE Receptionist_ID = '"+receptionist_id+"'");
        qry->exec();
        admin.connClose();

        QMessageBox *msgBox = new QMessageBox(this);
        msgBox->setIcon(QMessageBox::Information);
        msgBox->setText("Receptionist Updated Sucessfully.");
        msgBox->setWindowTitle("UPDATE");
        msgBox->exec();

        viewReceptionist();
    }

    ui->update_pushButton->setEnabled(false);
}

//Home and Logout BUTTONS
void ReceptionistDetail::on_home_pushButton_4_clicked()
{
    this->hide();
    Welcome *w = new Welcome(this);
    w->show();
}


void ReceptionistDetail::on_logout_pushButton_4_clicked()
{
    this->hide();
    Welcome *w = new Welcome(this);
    w->show();
}
//----------------------------------- end update doctor ------------------------------------------------------


