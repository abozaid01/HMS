#ifndef DOCTOR_H
#define DOCTOR_H

#include <QWidget>
#include "admin.h"

namespace Ui {
class Doctor;
}

class Doctor : public QWidget
{
    Q_OBJECT

public:
    explicit Doctor(QWidget *parent = nullptr);
    ~Doctor();

    const QString &getSex() const;
    void setSex(const QString &newSex);

    const QString &getName() const;
    void setName(const QString &newtName);

    QString getDOB() const;
    void setDOB(QString newDOB);

    QString getSSN() const;
    void setSSN(QString newSSN);

    const QString &getPhone_number() const;
    void setPhone_number(const QString &newPhone_number);

    const QString &getSalary() const;
    void setSalary(const QString &newSalary);

    const QString &getWork_Hours() const;
    void setWork_Hours(const QString &newWork_Hours);

    const QString &getDepartment() const;
    void setDepartment(const QString &newDepartment);

    const QString &getSpecialization() const;
    void setSpecialization(const QString &newSpecialization);

signals:

private:
    QString Name;
    QString DOB;
    QString SSN;
    QString Sex;
    QString phone_number;
    QString Salary;
    QString Work_Hours;
    QString Department;
    QString Specialization;
    Ui::Doctor *ui;
};

#endif // DOCTOR_H
