#include "doctor.h"
#include "ui_doctor.h"

Doctor::Doctor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Doctor)
{
    ui->setupUi(this);
}

Doctor::~Doctor()
{
    delete ui;
}

const QString &Doctor::getSex() const
{
    return Sex;
}

void Doctor::setSex(const QString &newSex)
{
    Sex = newSex;
}

const QString &Doctor::getName() const
{
    return Name;
}

void Doctor::setName(const QString &newName)
{
    Name = newName;
}


QString Doctor::getDOB() const
{
    return DOB;
}

void Doctor::setDOB(QString newDOB)
{
    DOB = newDOB;
}

QString Doctor::getSSN() const
{
    return SSN;
}

void Doctor::setSSN(QString newSSN)
{
    SSN = newSSN;
}

const QString &Doctor::getPhone_number() const
{
    return phone_number;
}

void Doctor::setPhone_number(const QString &newPhone_number)
{
    phone_number = newPhone_number;
}


const QString &Doctor::getSalary() const
{
    return Salary;
}

void Doctor::setSalary(const QString &newSalary)
{
    Salary = newSalary;
}

const QString &Doctor::getWork_Hours() const
{
    return Work_Hours;
}

void Doctor::setWork_Hours(const QString &newWork_Hours)
{
    Work_Hours = newWork_Hours;
}

const QString &Doctor::getDepartment() const
{
    return Department;
}

void Doctor::setDepartment(const QString &newDepartment)
{
    Department = newDepartment;
}

const QString &Doctor::getSpecialization() const
{
    return Specialization;
}

void Doctor::setSpecialization(const QString &newSpecialization)
{
    Specialization = newSpecialization;
}
