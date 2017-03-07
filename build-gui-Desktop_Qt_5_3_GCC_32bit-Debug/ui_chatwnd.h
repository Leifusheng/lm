/********************************************************************************
** Form generated from reading UI file 'chatwnd.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATWND_H
#define UI_CHATWND_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChatWnd
{
public:
    QTextEdit *input;
    QTextBrowser *record;
    QPushButton *send;
    QPushButton *send_file;

    void setupUi(QWidget *ChatWnd)
    {
        if (ChatWnd->objectName().isEmpty())
            ChatWnd->setObjectName(QStringLiteral("ChatWnd"));
        ChatWnd->resize(492, 427);
        input = new QTextEdit(ChatWnd);
        input->setObjectName(QStringLiteral("input"));
        input->setGeometry(QRect(10, 300, 471, 78));
        record = new QTextBrowser(ChatWnd);
        record->setObjectName(QStringLiteral("record"));
        record->setGeometry(QRect(10, 10, 471, 281));
        send = new QPushButton(ChatWnd);
        send->setObjectName(QStringLiteral("send"));
        send->setGeometry(QRect(380, 390, 99, 27));
        send_file = new QPushButton(ChatWnd);
        send_file->setObjectName(QStringLiteral("send_file"));
        send_file->setGeometry(QRect(10, 390, 99, 27));

        retranslateUi(ChatWnd);

        QMetaObject::connectSlotsByName(ChatWnd);
    } // setupUi

    void retranslateUi(QWidget *ChatWnd)
    {
        ChatWnd->setWindowTitle(QApplication::translate("ChatWnd", "Form", 0));
        send->setText(QApplication::translate("ChatWnd", "send", 0));
        send_file->setText(QApplication::translate("ChatWnd", "send file", 0));
    } // retranslateUi

};

namespace Ui {
    class ChatWnd: public Ui_ChatWnd {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATWND_H
