#include "App.h"
#include <QApplication>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include "../lm_def.h"
#include "chatwnd.h"

App::App(QObject *parent) :
    QObject(parent)
{
    uicontrol = new QUdpSocket;
    uicontrol->bind(UI_CONTROL_PORT);
    uifiletransmit = new QUdpSocket;
    uifiletransmit->bind(UI_FILETRANSMIT_PORT);

    connect(uicontrol, SIGNAL(readyRead()), this, SLOT(uiControlReadyRead()));

    userlist = new Userlist;
    //set close last window close the software
    qApp->setQuitOnLastWindowClosed(false);
    //create icon
    _icon = new QSystemTrayIcon(this);
    _icon->setIcon(QIcon(":/img/chat.png"));
    //add control menu
    controlnemu = new QMenu;
    controlnemu->addAction("open",  this, SLOT(slotOpen()));
    controlnemu->addAction("exit", qApp, SLOT(quit()));
    _icon->setContextMenu(controlnemu);
    _icon->show();
}

void App::slotOpen()
{
    userlist->show();
}

void App::slotSetusername(QString name)
{
    QJsonObject obj;
    obj.insert(LM_CMD, LM_SETNAME);
    obj.insert(LM_NAME, name);
    //send message to control
    QJsonDocument doc(obj);
    QByteArray buf = doc.toJson();
    //uicontrol->writeDatagram() old version
    uicontrol->writeDatagram(buf, QHostAddress::LocalHost, CONTROL_UI_PORT);
}

void App::uiControlReadyRead()
{
    //get next buf size
    int size = uicontrol->pendingDatagramSize();
    QByteArray buf(size, 0);
    uicontrol->readDatagram(buf.data(), buf.size());
    //
    QJsonDocument obj = QJsonDocument::fromJson(buf);
    QJsonObject root = obj.object();
    userlist->setuser(root.value(LM_NAME).toString(), root.value(LM_IP).toString());
    connect(userlist, SIGNAL(sigchatnewwnd(QString, QString)), this, SLOT(slotNewwnd(QString, QString)));

}

void App::slotnewmessage(QString msg, QString ip)
{
    QJsonObject obj;
    obj.insert(LM_CMD, LM_TO);
    obj.insert(LM_MSG, msg);
    obj.insert(LM_RECV, ip);
    QByteArray buf = QJsonDocument(obj).toJson();
    uicontrol->writeDatagram(buf, QHostAddress::LocalHost, CONTROL_UI_PORT);
}

void App::slotNewwnd(QString ip, QString name)
{
    if (chatwnds.find(ip) != chatwnds.end())
    {
        ChatWnd * wnd = chatwnds[ip];
        Qt::WindowFlags flags = wnd->windowFlags();
        flags |= Qt::WindowStaysOnTopHint;
        wnd->setWindowFlags(flags);
        wnd->show();
    }
    else
    {
        ChatWnd * wnd = new ChatWnd;
        wnd->ip = ip;
        QString title = QString("chat with %1").arg(name);
        wnd->setWindowTitle(title);
        wnd->show();
        chatwnds[ip] = wnd;
        connect(wnd, SIGNAL(signewmessage(QString, QString)), this, SLOT(slotNewwnd(QString,QString));
    }
}
