#include "App.h"
#include <QApplication>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QFileDialog>
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
    connect(userlist, SIGNAL(sigchatnewwnd(QString, QString)), this, SLOT(slotNewwnd(QString, QString)));
    //set close last window close the software
    qApp->setQuitOnLastWindowClosed(false);
    //create icon
    _icon = new QSystemTrayIcon(this);
    _icon->setIcon(QIcon(":/img/chat.png"));
    //add control menu
    controlnemu = new QMenu;
    controlnemu->addAction("open",  this, SLOT(slotOpen()));
    controlnemu->addAction("exit", qApp, SLOT(quit()));
    connect(this, SIGNAL(slgcancel()), qApp, SLOT(quit()));
    _icon->setContextMenu(controlnemu);
    _icon->show();
}

ChatWnd *App::getChatWnd(QString ip, QString name)
{
    ChatWnd * wnd;
    if (chatwnds.find(ip) != chatwnds.end())
    {
        wnd = chatwnds[ip];
        Qt::WindowFlags flags = wnd->windowFlags();
        flags |= Qt::WindowStaysOnTopHint;
        wnd->setWindowFlags(flags);
        wnd->show();
    }
    else
    {
        wnd = new ChatWnd;
        wnd->ip = ip;
        QString title = QString("chat with %1").arg(name);
        wnd->setWindowTitle(title);
        wnd->show();
        chatwnds[ip] = wnd;
        connect(wnd, SIGNAL(signewmessage(QString, QString)), this, SLOT(slotnewmessage(QString,QString)));
    }
    return wnd;
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

void App::soltcancelsetname()
{
    qDebug() << "cansel set name";
    emit slgcancel();
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
    //List ack
    QString cmd = root.value(LM_CMD).toString();
    if (cmd == LM_LIST_ACK)
    {
        userlist->setuser(root.value(LM_NAME).toString(), root.value(LM_IP).toString());
    }
    else if (cmd == LM_MSG)
    {
        /*
         *toui.add(LM_CMD, LM_MSG);
        toui.add(LM_FROM_NAME, by);
        toui.add(LM_FROM_IP, ip);
        toui.add(LM_MSG, msg);
        */
        QString ip = root.value(LM_IP).toString();
        QString name = root.value(LM_NAME).toString();
        QString broad = root.value(LM_IS_BROADCAST).toString();
        ChatWnd *wnd;
        if (broad == "1")
        {
            ip = "255.255.255.255";
            wnd = getChatWnd(ip, "all");
        }
        else
        {
            wnd = getChatWnd(ip, name);
        }
        QString msg = root.value(LM_MSG).toString();
        wnd->showMessage(name, msg);
    }
    else if (cmd == LM_FILETRANSMIT)
    {
        /*
         * ui_json.add(LM_CMD, LM_FILETRANSMIT);
        //who send file to me
        ui_json.add(LM_SEND, ip);
        ui_json.add(LM_TYPE, LM_RECV);
        ui_json.add(LM_TOKEN, json.value(LM_TOKEN));
        ui_json.add(LM_FILELEN, json.value(LM_FILELEN));
        ui_json.add(LM_FROM_NAME, json.value(LM_FROM_NAME));
        json.add(LM_ACK, LM_YES);
        json.add(LM_LOCAL_PATH, "/home/saul/Desktop/lm/test.file");
        */
        QString local_path = QFileDialog::getSaveFileName();
        if (local_path.size() == 0)
        {
            local_path = "/home/saul/Desktop/lm/test.file";
        }
        root.insert(LM_ACK, LM_YES);
        root.insert(LM_LOCAL_PATH, local_path);
        QByteArray buf = QJsonDocument(root).toJson();
        uicontrol->writeDatagram(buf, QHostAddress::LocalHost, CONTROL_UI_PORT);
    }
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
    getChatWnd(ip, name);
}

void App::slotsendfile(QString ip, QString path)
{
    /*
     * Json json;
        json.add(LM_CMD, LM_SENDFILE);
        json.add(LM_RECV, recvip);
        json.add(LM_FILEPATH, realpath_bk);
    */

    QJsonObject obj;
    obj.insert(LM_CMD, LM_SENDFILE);
    obj.insert(LM_FILEPATH, path);
    obj.insert(LM_RECV, ip);
    QByteArray buf = QJsonDocument(obj).toJson();
    uicontrol->writeDatagram(buf, QHostAddress::LocalHost, CONTROL_UI_PORT);
}
