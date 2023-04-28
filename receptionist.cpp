#include "receptionist.h"
#include "ui_receptionist.h"

Receptionist::Receptionist(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Receptionist)
{
    ui->setupUi(this);
}

Receptionist::~Receptionist()
{
    delete ui;
}

const QString &Receptionist::getGender() const
{
    return gender;
}

void Receptionist::setGender(const QString &newGender)
{
    gender = newGender;
}

const QString &Receptionist::getFirstName() const
{
    return firstName;
}

void Receptionist::setFirstName(const QString &newFirstName)
{
    firstName = newFirstName;
}

const QString &Receptionist::getLastName() const
{
    return lastName;
}

void Receptionist::setLastName(const QString &newLastName)
{
    lastName = newLastName;
}

QString Receptionist::getAge() const
{
    return age;
}

void Receptionist::setAge(QString newAge)
{
    age = newAge;
}

QString Receptionist::getId() const
{
    return id;
}

void Receptionist::setId(QString newId)
{
    id = newId;
}

const QString &Receptionist::getPhone_number() const
{
    return phone_number;
}

void Receptionist::setPhone_number(const QString &newPhone_number)
{
    phone_number = newPhone_number;
}

const QString &Receptionist::getAddress() const
{
    return address;
}

void Receptionist::setAddress(const QString &newAddress)
{
    address = newAddress;
}

const QString &Receptionist::getMarital_status() const
{
    return marital_status;
}

void Receptionist::setMarital_status(const QString &newMarital_status)
{
    marital_status = newMarital_status;
}

