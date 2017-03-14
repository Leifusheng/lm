#ifndef APP_H
#define APP_H

#include <QObject>
#include <QMenu>
#include <QSystemTrayIcon>
#include "userlist.h"
#include <QUdpSocket>
#include "chatwnd.h"
#include <QMap>

class App : public QObject
{
    Q_OBJECT
public:
    explicit App(QObject *parent = 0);
    QSystemTrayIcon* _icon;
    QMenu* controlnemu;
    Userlist* userlist;
    QUdpSocket* uicontrol;
    QUdpSocket* uifiletransmit;
    QMap<QString, ChatWnd *> chatwnds;
    ChatWnd* getChatWnd(QString ip, QString name);

signals:
public slots:
    void slotOpen();
    void slotSetusername(QString);
    void uiControlReadyRead();
    void slotnewmessage(QString msg, QString ip);
    void slotNewwnd(QString ip, QString name);
    void slotsendfile(QString ip, QString path);

};

#endif // APP_H
