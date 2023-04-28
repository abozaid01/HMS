#ifndef PATIENT_H
#define PATIENT_H

#include <QWidget>
#include <QDate>

class Patient : public QWidget
{
    Q_OBJECT
public:
    explicit Patient(QWidget *parent = nullptr);



    const QString &getGender() const;
    void setGender(const QString &newGender);

    const QString &getFirstName() const;
    void setFirstName(const QString &newFirstName);

    const QString &getLastName() const;
    void setLastName(const QString &newLastName);

    QString getAge() const;
    void setAge(QString newAge);

    QString getId() const;
    void setId(QString newId);

    const QString &getPhone_number() const;
    void setPhone_number(const QString &newPhone_number);

    const QString &getAddress() const;
    void setAddress(const QString &newAddress);

    const QString &getMarital_status() const;
    void setMarital_status(const QString &newMarital_status);

    const QDate &getDOB() const;
    void setDOB(const QDate &newDOB);


signals:

private:
    QString firstName;
    QString lastName;
    QString age;
    QString id;
    QString gender;
    QString phone_number;
    QString address;
    QString marital_status;
    QDate DOB;


};

#endif // PATIENT_H
