#include "chatwnd.h"
#include "ui_chatwnd.h"

ChatWnd::ChatWnd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatWnd)
{
    ui->setupUi(this);
}

ChatWnd::~ChatWnd()
{
    delete ui;
}

void ChatWnd::showMessage(QString name, QString msg)
{
    ui->record->append(name + " say:" + msg);
}

void ChatWnd::on_send_clicked()
{
    QString text = ui->input->toPlainText();
    ui->record->append("I say: " + text);
    ui->input->clear();
    emit signewmessage(text, ip);
}
