#include "setusername.h"
#include "ui_setusername.h"

SetUsername::SetUsername(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetUsername)
{
    ui->setupUi(this);
}

SetUsername::~SetUsername()
{
    delete ui;
}

void SetUsername::on_oksetname_clicked()
{
    if (ui->setname->text().size() == 0)
    {
        return;
    }
    else
    {
        QString name = ui->setname->text();
        emit signame(name);
        //close windows
        accept();
    }
}

void SetUsername::on_cancelsetname_clicked()
{

    emit sigcancel();
    accept();
}
