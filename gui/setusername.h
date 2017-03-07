#ifndef SETUSERNAME_H
#define SETUSERNAME_H

#include <QDialog>

namespace Ui {
class SetUsername;
}

class SetUsername : public QDialog
{
    Q_OBJECT

public:
    explicit SetUsername(QWidget *parent = 0);
    ~SetUsername();
signals:
    void signame(QString);
    void sigcancel();

private slots:
    void on_oksetname_clicked();

    void on_cancelsetname_clicked();

private:
    Ui::SetUsername *ui;
};

#endif // SETUSERNAME_H
