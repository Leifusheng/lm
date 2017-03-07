/********************************************************************************
** Form generated from reading UI file 'setusername.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETUSERNAME_H
#define UI_SETUSERNAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SetUsername
{
public:
    QVBoxLayout *verticalLayout_2;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLineEdit *setname;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *cancelsetname;
    QPushButton *oksetname;

    void setupUi(QDialog *SetUsername)
    {
        if (SetUsername->objectName().isEmpty())
            SetUsername->setObjectName(QStringLiteral("SetUsername"));
        SetUsername->resize(407, 141);
        verticalLayout_2 = new QVBoxLayout(SetUsername);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(9, 9, 9, 9);
        widget = new QWidget(SetUsername);
        widget->setObjectName(QStringLiteral("widget"));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(9, 9, 9, 9);
        setname = new QLineEdit(widget);
        setname->setObjectName(QStringLiteral("setname"));

        verticalLayout->addWidget(setname);


        verticalLayout_2->addWidget(widget);

        widget_2 = new QWidget(SetUsername);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        horizontalLayout = new QHBoxLayout(widget_2);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(9, 9, 9, 9);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        cancelsetname = new QPushButton(widget_2);
        cancelsetname->setObjectName(QStringLiteral("cancelsetname"));
        cancelsetname->setAutoDefault(false);

        horizontalLayout->addWidget(cancelsetname);

        oksetname = new QPushButton(widget_2);
        oksetname->setObjectName(QStringLiteral("oksetname"));

        horizontalLayout->addWidget(oksetname);


        verticalLayout_2->addWidget(widget_2);


        retranslateUi(SetUsername);

        QMetaObject::connectSlotsByName(SetUsername);
    } // setupUi

    void retranslateUi(QDialog *SetUsername)
    {
        SetUsername->setWindowTitle(QApplication::translate("SetUsername", "SetName", 0));
        cancelsetname->setText(QApplication::translate("SetUsername", "cancel", 0));
        oksetname->setText(QApplication::translate("SetUsername", "ok", 0));
    } // retranslateUi

};

namespace Ui {
    class SetUsername: public Ui_SetUsername {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETUSERNAME_H
