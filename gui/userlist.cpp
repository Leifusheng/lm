#include "userlist.h"
#include "ui_userlist.h"

Userlist::Userlist(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Userlist)
{
    ui->setupUi(this);
}

Userlist::~Userlist()
{
    delete ui;
}

void Userlist::setuser(QString name, QString ip)
{
    //if ip is not exist not add
    //if ip not exist add
    int count = ui->listWidget->count();
    int i;
    for (i = 0; i < count; ++i)
    {
        QListWidgetItem* item = ui->listWidget->item(i);
        if (item->data(Qt::UserRole).toString() == ip)
        {
            QString label = name + "(" + ip + ")";
            item->setData(Qt::DisplayRole, label);
            item->setData(Qt::UserRole+1, name);
            break;
        }
    }
    if (i == count)
    {
        QListWidgetItem* item = new QListWidgetItem;
        QString label = name + "(" + ip + ")";
        item->setData(Qt::DisplayRole, label);
        item->setData(Qt::UserRole, ip);
        item->setData(Qt::UserRole+1, name);
        ui->listWidget->addItem(item);
    }
}



void Userlist::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    QString ip = item->data(Qt::UserRole).toString();
    QString name = item->data(Qt::UserRole+1).toString();
    emit sigchatnewwnd(ip, name);
}
