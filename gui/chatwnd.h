#ifndef CHATWND_H
#define CHATWND_H

#include <QWidget>

namespace Ui {
class ChatWnd;
}

class ChatWnd : public QWidget
{
    Q_OBJECT

public:
    explicit ChatWnd(QWidget *parent = 0);
    ~ChatWnd();
    void showMessage(QString name, QString msg);
    QString ip;
signals:
    void signewmessage(QString msg, QString ip);
private slots:
    void on_send_clicked();

private:
    Ui::ChatWnd *ui;
};

#endif // CHATWND_H
