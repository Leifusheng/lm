#include "userlist.h"
#include "ui_userlist.h"

Userlist::Userlist(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Userlist)
{
    ui->setupUi(this);
    QListWidgetItem* item = new QListWidgetItem;
    QString label = "all(255.255.255.255)";
    item->setData(Qt::DisplayRole, label);
    item->setData(Qt::UserRole, "255.255.255.255");
    item->setData(Qt::UserRole+1, "all");
    ui->listWidget->addItem(item);
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
