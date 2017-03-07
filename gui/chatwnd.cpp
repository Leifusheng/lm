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

void ChatWnd::on_send_clicked()
{
    QString text = ui->input->toPlainText();
    emit signewmessage(text, ip);
}
