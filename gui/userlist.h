#ifndef USERLIST_H
#define USERLIST_H

#include <QWidget>
#include <QListWidgetItem>


namespace Ui {
class Userlist;
}

class Userlist : public QWidget
{
    Q_OBJECT

public:
    explicit Userlist(QWidget *parent = 0);
    ~Userlist();

    void setuser(QString name, QString ip);
signals:
    void sigchatnewwnd(QString ip, QString name);

private slots:

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::Userlist *ui;
};

#endif // USERLIST_H
