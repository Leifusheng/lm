/********************************************************************************
** Form generated from reading UI file 'userlist.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERLIST_H
#define UI_USERLIST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Userlist
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QListWidget *listWidget;

    void setupUi(QWidget *Userlist)
    {
        if (Userlist->objectName().isEmpty())
            Userlist->setObjectName(QStringLiteral("Userlist"));
        Userlist->resize(249, 497);
        verticalLayout = new QVBoxLayout(Userlist);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(Userlist);
        label->setObjectName(QStringLiteral("label"));
        label->setFrameShape(QFrame::WinPanel);
        label->setTextFormat(Qt::RichText);

        verticalLayout->addWidget(label);

        widget = new QWidget(Userlist);
        widget->setObjectName(QStringLiteral("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        listWidget = new QListWidget(widget);
        listWidget->setObjectName(QStringLiteral("listWidget"));

        horizontalLayout->addWidget(listWidget);


        verticalLayout->addWidget(widget);


        retranslateUi(Userlist);

        QMetaObject::connectSlotsByName(Userlist);
    } // setupUi

    void retranslateUi(QWidget *Userlist)
    {
        Userlist->setWindowTitle(QApplication::translate("Userlist", "Form", 0));
        label->setText(QApplication::translate("Userlist", "Friend list:", 0));
    } // retranslateUi

};

namespace Ui {
    class Userlist: public Ui_Userlist {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERLIST_H
