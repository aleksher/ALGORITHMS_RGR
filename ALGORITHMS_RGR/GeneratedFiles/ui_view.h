/********************************************************************************
** Form generated from reading UI file 'view.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIEW_H
#define UI_VIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_View
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QGroupBox *gbPlayMode;
    QVBoxLayout *verticalLayout_2;
    QRadioButton *rbBandit;
    QRadioButton *rbPoliceman;
    QGroupBox *gbLevel;
    QVBoxLayout *verticalLayout_3;
    QSpinBox *sbAILevel;
    QPushButton *pbPlay;
    QSpacerItem *verticalSpacer;

    void setupUi(QMainWindow *View)
    {
        if (View->objectName().isEmpty())
            View->setObjectName(QStringLiteral("View"));
        View->resize(515, 400);
        View->setMinimumSize(QSize(515, 400));
        View->setMaximumSize(QSize(515, 400));
        View->setBaseSize(QSize(500, 400));
        centralWidget = new QWidget(View);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setMinimumSize(QSize(100, 0));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(-1, 0, 0, -1);
        gbPlayMode = new QGroupBox(widget);
        gbPlayMode->setObjectName(QStringLiteral("gbPlayMode"));
        gbPlayMode->setMinimumSize(QSize(0, 0));
        verticalLayout_2 = new QVBoxLayout(gbPlayMode);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        rbBandit = new QRadioButton(gbPlayMode);
        rbBandit->setObjectName(QStringLiteral("rbBandit"));
        rbBandit->setChecked(true);

        verticalLayout_2->addWidget(rbBandit);

        rbPoliceman = new QRadioButton(gbPlayMode);
        rbPoliceman->setObjectName(QStringLiteral("rbPoliceman"));

        verticalLayout_2->addWidget(rbPoliceman);


        verticalLayout->addWidget(gbPlayMode);

        gbLevel = new QGroupBox(widget);
        gbLevel->setObjectName(QStringLiteral("gbLevel"));
        verticalLayout_3 = new QVBoxLayout(gbLevel);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        sbAILevel = new QSpinBox(gbLevel);
        sbAILevel->setObjectName(QStringLiteral("sbAILevel"));
        sbAILevel->setMinimum(1);
        sbAILevel->setMaximum(4);
        sbAILevel->setValue(3);

        verticalLayout_3->addWidget(sbAILevel);


        verticalLayout->addWidget(gbLevel);

        pbPlay = new QPushButton(widget);
        pbPlay->setObjectName(QStringLiteral("pbPlay"));

        verticalLayout->addWidget(pbPlay);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addWidget(widget);

        View->setCentralWidget(centralWidget);

        retranslateUi(View);

        QMetaObject::connectSlotsByName(View);
    } // setupUi

    void retranslateUi(QMainWindow *View)
    {
        View->setWindowTitle(QApplication::translate("View", "View", nullptr));
        gbPlayMode->setTitle(QApplication::translate("View", "Play mode", nullptr));
        rbBandit->setText(QApplication::translate("View", "bandit", nullptr));
        rbPoliceman->setText(QApplication::translate("View", "policeman", nullptr));
        gbLevel->setTitle(QApplication::translate("View", "Level", nullptr));
        pbPlay->setText(QApplication::translate("View", "Start", nullptr));
    } // retranslateUi

};

namespace Ui {
    class View: public Ui_View {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEW_H
