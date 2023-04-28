#ifndef WELCOME_H
#define WELCOME_H

#include <QMainWindow>

namespace Ui {
class Welcome;
}

class Welcome : public QMainWindow
{
    Q_OBJECT

public:
    explicit Welcome(QWidget *parent = nullptr);
    ~Welcome();

private slots:
    void on_adminPushButton_clicked();
    void on_receptionstPushButton_clicked();
    void on_doctorPushButton_clicked();


private:
    Ui::Welcome *ui;
};

#endif // WELCOME_H
