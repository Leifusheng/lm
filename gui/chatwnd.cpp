#include "chatwnd.h"
#include "ui_chatwnd.h"
#include <QFileDialog>

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

void ChatWnd::on_send_file_clicked()
{
    QString filename = QFileDialog::getOpenFileName();
    if (filename.size() > 0)
    {
        QString label = "notify: send " + filename;
        ui->record->append(label);
        emit sigsendfile(ip, filename);
    }
}
