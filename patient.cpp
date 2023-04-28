#include "patient.h"
#include "patientdetail.h"

Patient::Patient(QWidget *parent)
    : QWidget{parent}
{

}


const QString &Patient::getGender() const
{
    return gender;
}

void Patient::setGender(const QString &newGender)
{
    gender = newGender;
}

const QString &Patient::getFirstName() const
{
    return firstName;
}

void Patient::setFirstName(const QString &newFirstName)
{
    firstName = newFirstName;
}

const QString &Patient::getLastName() const
{
    return lastName;
}

void Patient::setLastName(const QString &newLastName)
{
    lastName = newLastName;
}

QString Patient::getAge() const
{
    return age;
}

void Patient::setAge(QString newAge)
{
    age = newAge;
}

QString Patient::getId() const
{
    return id;
}

void Patient::setId(QString newId)
{
    id = newId;
}

const QString &Patient::getPhone_number() const
{
    return phone_number;
}

void Patient::setPhone_number(const QString &newPhone_number)
{
    phone_number = newPhone_number;
}

const QString &Patient::getAddress() const
{
    return address;
}

void Patient::setAddress(const QString &newAddress)
{
    address = newAddress;
}

const QString &Patient::getMarital_status() const
{
    return marital_status;
}

void Patient::setMarital_status(const QString &newMarital_status)
{
    marital_status = newMarital_status;
}

const QDate &Patient::getDOB() const
{
    return DOB;
}

void Patient::setDOB(const QDate &newDOB)
{
    DOB = newDOB;
}
