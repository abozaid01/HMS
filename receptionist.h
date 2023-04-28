#ifndef RECEPTIONIST_H
#define RECEPTIONIST_H

#include <QWidget>
#include "admin.h"

namespace Ui {
class Receptionist;
}

class Receptionist : public QWidget
{
    Q_OBJECT

public:
    explicit Receptionist(QWidget *parent = nullptr);
    ~Receptionist();

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
    Ui::Receptionist *ui;
};

#endif // RECEPTIONIST_H

